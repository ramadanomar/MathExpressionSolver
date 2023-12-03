#include "pch.h"
#include "CppUnitTest.h"
#include "../MathExpressionSolver/Menu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestAdditionAndMultiplication)
        {
            Menu menu;
            double result = menu.calculateExpression(std::string("[40+(5-1)]*2"));
            Assert::AreEqual(88.0, result, 0.001);
        }

        TEST_METHOD(TestDivisionByZero)
        {
            Menu menu;
            auto func = [&] { menu.calculateExpression(std::string("5 / 0")); };
            Assert::ExpectException<std::runtime_error>(func);
        }

        TEST_METHOD(TestComplexExpression)
        {
            Menu menu;
            double result = menu.calculateExpression(std::string("[(2*3)^2]/4-(6+2)#3"));
            Assert::AreEqual(7.0, result, 0.001);
        }

        TEST_METHOD(TestDecimalMultiplication)
        {
            Menu menu;
            double result = menu.calculateExpression(std::string("2 * 3.2"));
            Assert::AreEqual(6.4, result, 0.001);
        }

        TEST_METHOD(TestSubtraction)
        {
            Menu menu;
            double result = menu.calculateExpression(std::string("24342343.0002-3"));
            Assert::AreEqual(24342340.0002, result, 0.0001);
        }

        TEST_METHOD(TestArithmeticOperations)
        {
            Menu menu;
            double result = menu.calculateExpression(std::string("2 * 3 - 8"));
            Assert::AreEqual(-2.0, result, 0.001);
        }
    };
}
