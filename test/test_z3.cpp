
#include "Encodings/Encodings.hpp"
#include "LogicBlock/Z3Logic.hpp"
#include "LogicTerm/Logic.hpp"
#include "LogicTerm/LogicTerm.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
class TestZ3: public testing::TestWithParam<logicbase::OpType> {
protected:
    void SetUp() override {
    }
};
TEST(TestZ3, ConstructDestruct) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    std::unique_ptr<z3logic::Z3LogicBlock> z3logic = std::make_unique<z3logic::Z3LogicBlock>(ctx, solver, false);
}

TEST(TestZ3, SimpleTrue) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    z3logic::Z3LogicBlock z3logic(ctx, solver, false);

    LogicTerm a = z3logic.makeVariable("a", CType::BOOL);
    LogicTerm b = z3logic.makeVariable("b", CType::BOOL);
    LogicTerm c = z3logic.makeVariable("c", CType::BOOL);

    z3logic.assertFormula(a && b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a || b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a == b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a != b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a && !b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a || !b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(LogicTerm::implies(a, b));
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);
    c = z3logic.makeVariable("c", CType::BOOL);

    z3logic.assertFormula(a && b && c);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a           = z3logic.makeVariable("a", CType::BOOL);
    b           = z3logic.makeVariable("b", CType::BOOL);
    c           = z3logic.makeVariable("c", CType::BOOL);
    LogicTerm d = z3logic.makeVariable("d", CType::BOOL);

    z3logic.assertFormula((a && b) || (c && d));
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();
}

TEST(TestZ3, SimpleFalse) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    z3logic::Z3LogicBlock z3logic(ctx, solver, false);

    LogicTerm a = z3logic.makeVariable("a", CType::BOOL);
    LogicTerm b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a);
    z3logic.assertFormula(a);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!b);
    z3logic.assertFormula(b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a);
    z3logic.assertFormula(b);
    z3logic.assertFormula(a == b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a);
    z3logic.assertFormula(!b);
    z3logic.assertFormula(a == b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a);
    z3logic.assertFormula(b);
    z3logic.assertFormula(a == b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a);
    z3logic.assertFormula(b);
    z3logic.assertFormula(a != b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a);
    z3logic.assertFormula(!b);
    z3logic.assertFormula(a != b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(!a);
    z3logic.assertFormula(!b);
    z3logic.assertFormula(a && !b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a);
    z3logic.assertFormula(b);
    z3logic.assertFormula(a && !b);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::BOOL);
    b = z3logic.makeVariable("b", CType::BOOL);

    z3logic.assertFormula(a);
    z3logic.assertFormula(!b);
    z3logic.assertFormula(LogicTerm::implies(a, b));
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::UNSAT);

    z3logic.reset();
}

TEST(TestZ3, IntBase) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    z3logic::Z3LogicBlock z3logic(ctx, solver, false);

    LogicTerm a = z3logic.makeVariable("a", CType::INT);
    LogicTerm b = z3logic.makeVariable("b", CType::INT);
    LogicTerm c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a + b == c);
    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a - b == c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a * b == c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a / b == c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);

    z3logic.assertFormula(a > b);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a < c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);

    z3logic.assertFormula(a >= b);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a <= c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();
}
TEST(TestZ3, IntNumbers) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    z3logic::Z3LogicBlock z3logic(ctx, solver, false);

    LogicTerm a = z3logic.makeVariable("a", CType::INT);
    LogicTerm b = z3logic.makeVariable("b", CType::INT);
    LogicTerm c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula(a - b == c);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula(c + b == a);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula((a > b) == LogicTerm(true));
    z3logic.assertFormula((b > c) == LogicTerm(true));

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula((c < a) == LogicTerm(true));
    z3logic.assertFormula((a < LogicTerm(4)) == LogicTerm(true));

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    LogicTerm bool_a = z3logic.makeVariable("bool_a", CType::BOOL);

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula(LogicTerm::ite(bool_a, a, b) == a);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();

    bool_a = z3logic.makeVariable("bool_a", CType::BOOL);

    a = z3logic.makeVariable("a", CType::INT);
    b = z3logic.makeVariable("b", CType::INT);
    c = z3logic.makeVariable("c", CType::INT);

    z3logic.assertFormula(a == LogicTerm(3));
    z3logic.assertFormula(b == LogicTerm(2));
    z3logic.assertFormula(c == LogicTerm(1));
    z3logic.assertFormula(LogicTerm::ite(bool_a, a, b) == b);

    z3logic.produceInstance();
    z3logic.dumpZ3State(std::cout);

    EXPECT_EQ(z3logic.solve(), Result::SAT);

    z3logic.reset();
}

TEST(TestZ3, AMOAndExactlyOneNaive) {
    using namespace logicbase;

    z3::context ctx{};
    z3::solver  solver{ctx};

    std::unique_ptr<z3logic::Z3LogicBlock> z3logic = std::make_unique<z3logic::Z3LogicBlock>(ctx, solver, false);

    std::vector<std::vector<LogicTerm>> a_nodes;

    for (int i = 0; i < 4; ++i) {
        a_nodes.emplace_back();
        for (int j = 0; j < 4; ++j) {
            a_nodes.back().emplace_back(z3logic->makeVariable("a_" + std::to_string(i) + "_" + std::to_string(j), CType::BOOL));
        }
    }

    for (int i = 0; i < 4; ++i) {
        LogicTerm a_ = LogicTerm(0);
        for (int j = 0; j < 4; ++j) {
            a_ = a_ + LogicTerm::ite(a_nodes[i][j], LogicTerm(1), LogicTerm(0));
        }
        LogicTerm aa = (a_ <= LogicTerm(1));
        z3logic->assertFormula(aa);
    }
    for (int i = 0; i < 4; ++i) {
        LogicTerm a_ = LogicTerm(0);
        for (int j = 0; j < 4; ++j) {
            a_ = a_ + LogicTerm::ite(a_nodes[j][i], LogicTerm(1), LogicTerm(0));
        }
        LogicTerm aa = (a_ == LogicTerm(1));
        z3logic->assertFormula(aa);
    }

    z3logic->produceInstance();
    z3logic->dumpZ3State(std::cout);

    EXPECT_EQ(z3logic->solve(), Result::SAT);

    z3logic.reset();
}

TEST(TestZ3, AMOAndExactlyOneCMDR) {
    using namespace logicbase;

    int n = 11;

    z3::context ctx{};
    z3::solver  solver{ctx};

    std::unique_ptr<z3logic::Z3LogicBlock> z3logic = std::make_unique<z3logic::Z3LogicBlock>(ctx, solver, false);

    std::vector<std::vector<LogicTerm>> a_nodes;

    for (int i = 0; i < n; ++i) {
        a_nodes.emplace_back();
        for (int j = 0; j < n; ++j) {
            a_nodes.back().emplace_back(z3logic->makeVariable("a_" + std::to_string(i) + "_" + std::to_string(j), CType::BOOL));
        }
    }

    for (int i = 0; i < n; ++i) {
        std::vector<LogicTerm> a_;
        for (int j = 0; j < n; ++j) {
            a_.emplace_back(a_nodes[i][j]);
        }
        LogicTerm aa = ExactlyOneCMDR(groupVars(a_, 3), LogicTerm::noneTerm(), z3logic.get());
        z3logic->assertFormula(aa);
    }
    for (int i = 0; i < n; ++i) {
        std::vector<LogicTerm> a_;
        for (int j = 0; j < n; ++j) {
            a_.emplace_back(a_nodes[i][j]);
        }
        LogicTerm aa = AtMostOneCMDR(groupVars(a_, 3), LogicTerm::noneTerm(), z3logic.get());
        z3logic->assertFormula(aa);
    }

    z3logic->produceInstance();
    z3logic->dumpZ3State(std::cout);

    EXPECT_EQ(z3logic->solve(), Result::SAT);

    z3logic.reset();
}

TEST(TestZ3, AMOAndExactlyOneBimander) {
    using namespace logicbase;

    int n = 11;

    z3::context ctx{};
    z3::solver  solver{ctx};

    std::unique_ptr<z3logic::Z3LogicBlock> z3logic = std::make_unique<z3logic::Z3LogicBlock>(ctx, solver, false);

    std::vector<std::vector<LogicTerm>> a_nodes;

    for (int i = 0; i < n; ++i) {
        a_nodes.emplace_back();
        for (int j = 0; j < n; ++j) {
            a_nodes.back().emplace_back(z3logic->makeVariable("a_" + std::to_string(i) + "_" + std::to_string(j), CType::BOOL));
        }
    }

    for (int i = 0; i < n; ++i) {
        std::vector<LogicTerm> a_;
        for (int j = 0; j < n; ++j) {
            a_.emplace_back(a_nodes[i][j]);
        }
        LogicTerm aa = ExactlyOneCMDR(groupVars(a_, 3), LogicTerm::noneTerm(), z3logic.get());
        z3logic->assertFormula(aa);
    }
    for (int i = 0; i < n; ++i) {
        std::vector<LogicTerm> a_;
        for (int j = 0; j < n; ++j) {
            a_.emplace_back(a_nodes[i][j]);
        }
        LogicTerm aa = AtMostOneBiMander(a_, z3logic.get());
        z3logic->assertFormula(aa);
    }

    z3logic->produceInstance();
    z3logic->dumpZ3State(std::cout);

    EXPECT_EQ(z3logic->solve(), Result::SAT);

    z3logic.reset();
}

TEST(TestZ3, BuildBDDTest) {
    using namespace logicbase;

    int n = 23;

    z3::context ctx{};
    z3::solver  solver{ctx};

    std::unique_ptr<z3logic::Z3LogicBlock> z3logic = std::make_unique<z3logic::Z3LogicBlock>(ctx, solver, false);

    std::vector<std::vector<LogicTerm>> a_nodes;

    for (int i = 0; i < n; ++i) {
        a_nodes.emplace_back();
        for (int j = 0; j < n; ++j) {
            a_nodes.back().emplace_back(z3logic->makeVariable("a_" + std::to_string(i) + "_" + std::to_string(j), CType::BOOL));
        }
    }

    for (int i = 0; i < n; ++i) {
        std::set<WeightedVar> a_;
        for (int j = 0; j < n; ++j) {
            a_.insert(WeightedVar(a_nodes[i][j], i + j));
        }
        LogicTerm aa = BuildBDD(a_, a_nodes[i], n, z3logic.get());
        z3logic->assertFormula(aa);
    }

    z3logic->produceInstance();
    z3logic->dumpZ3State(std::cout);

    EXPECT_EQ(z3logic->solve(), Result::SAT);

    z3logic.reset();
}
