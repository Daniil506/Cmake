#include <gtest/gtest.h>
#include "stack.h"
#include <stdexcept>

TEST(StackOnMassTest, Initialization) {
    StackOnMass<int> stack(5);

    EXPECT_EQ(stack.get_size(), 5);
    EXPECT_EQ(stack.get_top(), -1);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
}

TEST(StackOnMassTest, PushElements) {
    StackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);

    EXPECT_EQ(stack.get_top(), 1);
    EXPECT_EQ(stack.top(), 20);
    EXPECT_FALSE(stack.is_empty());
}

TEST(StackOnMassTest, PopElements) {
    StackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);

    EXPECT_TRUE(stack.is_empty());
}

TEST(StackOnMassTest, StackBecomesFull) {
    StackOnMass<int> stack(2);

    stack.push(10);
    stack.push(20);

    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(stack.get_top(), 1);
}

TEST(StackOnMassTest, CopyConstructor) {
    StackOnMass<int> stack1(3);

    stack1.push(10);
    stack1.push(20);

    StackOnMass<int> stack2(stack1);

    EXPECT_EQ(stack2.get_size(), 3);
    EXPECT_EQ(stack2.get_top(), 1);
    EXPECT_EQ(stack2.pop(), 20);
    EXPECT_EQ(stack2.pop(), 10);

    EXPECT_EQ(stack1.top(), 20);
    EXPECT_FALSE(stack1.is_empty());
}

TEST(StackOnMassTest, ThrowOnPushToFull) {
    StackOnMass<int> stack(2);

    stack.push(10);
    stack.push(20);

    EXPECT_THROW(stack.push(30), std::out_of_range);
}

TEST(StackOnMassTest, ThrowOnPopFromEmpty) {
    StackOnMass<int> stack(3);

    EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(StackOnMassTest, ThrowOnTopFromEmpty) {
    StackOnMass<int> stack(3);

    EXPECT_THROW(stack.top(), std::out_of_range);
}

TEST(StackOnMassTest, PushWithEvictionToNotFullStack) {
    StackOnMass<int> stack(3);

    stack.push_with_eviction(10);
    stack.push_with_eviction(20);

    EXPECT_EQ(stack.get_top(), 1);
    EXPECT_EQ(stack.top(), 20);

    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.pop(), 10);
}

TEST(StackOnMassTest, PushWithEvictionToFullStack) {
    StackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.push_with_eviction(40);

    EXPECT_EQ(stack.get_size(), 3);
    EXPECT_EQ(stack.get_top(), 2);
    EXPECT_EQ(stack.top(), 40);

    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.pop(), 30);
    EXPECT_EQ(stack.pop(), 20);

    EXPECT_TRUE(stack.is_empty());
}

TEST(StackOnMassTest, PushWithEvictionRemovesOldestElement) {
    StackOnMass<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.push_with_eviction(40);
    stack.push_with_eviction(50);

    EXPECT_EQ(stack.pop(), 50);
    EXPECT_EQ(stack.pop(), 40);
    EXPECT_EQ(stack.pop(), 30);

    EXPECT_TRUE(stack.is_empty());
}

TEST(StackOnMassTest, PushWithEvictionKeepsStackSize) {
    StackOnMass<int> stack(2);

    stack.push(10);
    stack.push(20);

    stack.push_with_eviction(30);

    EXPECT_EQ(stack.get_size(), 2);
    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(stack.get_top(), 1);
}

TEST(StackOnMassTest, ThrowOnPushWithEvictionToZeroSizeStack) {
    StackOnMass<int> stack(0);

    EXPECT_THROW(stack.push_with_eviction(10), std::out_of_range);
}