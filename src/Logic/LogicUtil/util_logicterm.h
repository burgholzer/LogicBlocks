#ifndef util_logicterm_h
#define util_logicterm_h
#include "../LogicTerm/LogicTerm.hpp"
#include "Logic.hpp"
#include "util_logic.h"
#include <algorithm>

namespace logicutil {
using namespace logicbase;
inline std::shared_ptr<TermImpl>
combineTerms(const LogicTerm &a, const LogicTerm &b, OpType op, Logic *logic) {
  if (a.getOpType() == op && b.getOpType() == op && isAssociative(op)) {
    std::vector<LogicTerm> terms{};
    terms.reserve(a.getNodes().size() + b.getNodes().size());

    auto res = getFlatTerms(a, op);
    terms.insert(terms.end(), res.begin(), res.end());
    res = getFlatTerms(b, op);
    terms.insert(terms.end(), res.begin(), res.end());

    return std::make_shared<TermImpl>(op, terms, getTargetCType(a, b), logic);
  }
  return std::make_shared<TermImpl>(op, a, b, getTargetCType(a, b), logic);
};

inline std::shared_ptr<TermImpl> combineOneConst(const LogicTerm &constant,
                                                 const LogicTerm &other,
                                                 OpType op, Logic *logic) {
  switch (op) { // TODO handle other CTypes
  case OpType::AND: {
    if (constant.getBoolValue() == true)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(false);
  }; break;
  case OpType::OR: {
    if (constant.getBoolValue() == false)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(true);
  }; break;
  case OpType::ADD: {
    if (constant.getFloatValue() == 0)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(OpType::ADD, other, constant,
                                        CType::INT, logic);
  }; break;
  case OpType::SUB: {
    if (constant.getFloatValue() == 0)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(OpType::SUB, other, constant,
                                        CType::INT, logic);
  }; break;
  case OpType::MUL: {
    if (constant.getFloatValue() == 0)
      return std::make_shared<TermImpl>(0);
    else if (constant.getFloatValue() == 1)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(OpType::MUL, other, constant,
                                        CType::INT, logic);
  }; break;
  case OpType::DIV: {
    if (constant.getFloatValue() == 0)
      throw std::runtime_error("Divide by zero");
    if (constant.getFloatValue() == 1)
      return other.getImplementation();
    else
      return std::make_shared<TermImpl>(OpType::DIV, other, constant,
                                        CType::INT, logic);
  }; break;
  default: // TODO there are multiple ctypes
    return std::make_shared<TermImpl>(op, other, constant, getCType(op), logic);
    break;
  }
};

inline std::shared_ptr<TermImpl>
combineConst(const LogicTerm &a, const LogicTerm &b, OpType op, Logic *logic) {
  if (!isConst(a) && !isConst(b)) {
    // erroneous function call
    throw std::runtime_error("Both terms are not constants");
  } else if (isConst(a) && isConst(b)) {
    // combine the values, return new const
    switch (op) {
    case OpType::AND:
      return std::make_shared<TermImpl>(a.getBoolValue() && b.getBoolValue());
    case OpType::OR:
      return std::make_shared<TermImpl>(a.getBoolValue() || b.getBoolValue());
    case OpType::IMPL:
      return std::make_shared<TermImpl>(!a.getBoolValue() || b.getBoolValue());
    case OpType::ADD:
      return std::make_shared<TermImpl>(a.getIntValue() + b.getIntValue());
    case OpType::SUB:
      return std::make_shared<TermImpl>(a.getIntValue() - b.getIntValue());
    case OpType::MUL:
      return std::make_shared<TermImpl>(a.getIntValue() * b.getIntValue());
    case OpType::DIV:
      return std::make_shared<TermImpl>(a.getIntValue() / b.getIntValue());
    case OpType::GT:
      return std::make_shared<TermImpl>(a.getIntValue() > b.getIntValue());
    case OpType::LT:
      return std::make_shared<TermImpl>(a.getIntValue() < b.getIntValue());
    case OpType::EQ:
      return std::make_shared<TermImpl>(a.getFloatValue() == b.getFloatValue());
    case OpType::XOR:
      return std::make_shared<TermImpl>(a.getFloatValue() != b.getFloatValue());
    default:
      throw std::runtime_error("Invalid operator");
    }
  } else if (isConst(a) && isCommutative(op)) {
    // since the combineOneConst ignores order of operands
    return combineOneConst(a, b, op, logic);
  } else if (isConst(b)) {
    // const comes at the end anyway
    return combineOneConst(b, a, op, logic);
  } else {
    // combineTerms respects order of operands
    return combineTerms(a, b, op, logic);
  }
  throw std::runtime_error("Invalid combination");
};

inline std::shared_ptr<TermImpl> negateTerm(const LogicTerm &term,
                                            Logic *logic) {
  if (isConst(term)) {
    switch (term.getCType()) {
    case logicbase::CType::BOOL:
      return std::make_shared<TermImpl>(!term.getBoolValue());
    case logicbase::CType::INT:
      return std::make_shared<TermImpl>(-term.getIntValue());
    case logicbase::CType::REAL:
      return std::make_shared<TermImpl>(-term.getFloatValue());
    default:
      throw std::runtime_error("Invalid CType");
    }
  } else if (term.getOpType() == OpType::NEG) {
    return static_cast<LogicTerm>(*term.getNodes().begin()).getImplementation();
  } else {
    return std::make_shared<TermImpl>(OpType::NEG, term, term.getCType(),
                                      logic);
  };
}

inline unsigned long long getMax(const std::vector<LogicTerm> &terms) {
  unsigned long long ret = 0;
  for (auto &it : terms)
    ret = std::max(ret, it.getDepth());
  return ret + 1;
}

} // namespace logicutil
#endif // LOGICBASE_TERM_IMPL_H