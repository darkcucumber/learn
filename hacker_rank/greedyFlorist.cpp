#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <cassert>

struct Flower;
struct Customer;

using PriceContainer = std::vector<Flower>;
using CustomerContainer = std::deque<Customer>;

struct Flower
{
	int mPrice;
	int mIndex;
	Flower(int price, int index) : mPrice(price), mIndex(index) {} 
	int GetPrice() const { return mPrice; }
	int GetIndex() const { return mIndex; }
};

struct Customer
{
	int mBought;
	Customer() : mBought(0) {}
	int GetBought() const { return mBought; }
	void IncrementPurchase() { ++mBought; }
};

void ReadFlowers(PriceContainer & prices, const int howMany)
{
	int tmp;
	for (int i = 0 ; std::cin.good() ; ++i)
	{
		std::cin >> tmp;
		prices.emplace_back( Flower(tmp, i) );
	}	
}

void PrintFlowers(const PriceContainer & prices)
{
	printf("Listing flower prices and indices:\n");
	for (const auto item : prices)
	{
		printf("%d %d\n", item.GetPrice(), item.GetIndex());
	}
	printf("\n");
	fflush(stdout);
}

void SortFlowers(PriceContainer & prices);

void PreprocessFlowers(PriceContainer & prices)
{
	SortFlowers(prices);
}

void SortFlowers(PriceContainer & prices)
{
	std::sort(	prices.begin(), 
				prices.end(), 
				[] (Flower lhs, Flower rhs) -> bool 
				{ return lhs.GetPrice() < rhs.GetPrice(); });
}

inline int GetPrice(PriceContainer & prices, const int position, const int bought)
{
	assert( bought >= 0 && position < prices.size() );
	return prices[position].GetPrice() * (1 + bought);
}

void ShiftCustomer(CustomerContainer & customers)
{
	// printf("Shifting customer with purchases: %d\n", customers.at(0).GetBought());
	Customer tmp = customers.at(0);
	customers.pop_front();
	customers.push_back(tmp);
}

void PrintCustomers(CustomerContainer & customers)
{
	for (const auto item : customers)
	{
		printf("%d ", item);
	}
	printf("\n"); fflush(stdout);
}

int BuyFlower(PriceContainer & prices, CustomerContainer & customers)
{
	assert( customers.size() );
	// PrintCustomers(customers);
	int flowerCost = 0;

	// buy the most expensive flower with the customer having the least amount of purchases
	flowerCost = (customers.at( 0 ).GetBought() + 1) * 
				 prices.at( prices.size() - 1 ).GetPrice();
	// printf("Buying %d %d for %d (customer pur. %d)\n", 	prices.at(  prices.size() - 1 ).GetPrice(), 
	// 													prices.at(  prices.size() - 1 ).GetIndex(), 
	// 													flowerCost, 
	// 													customers.at(0).GetBought());
	customers.at( 0 ).IncrementPurchase();
	ShiftCustomer(customers);

	prices.erase(prices.end() - 1);

	return flowerCost;
}

int CalculateCost(PriceContainer & prices, const int nFlowers, const int customers)
{
	assert(nFlowers >= 0 && customers >= 0);
	int totalFlowersBought = 0;
	int flowerCost = 0;
	CustomerContainer customerContainer(customers);

	while (totalFlowersBought < nFlowers)
	{
		flowerCost += BuyFlower(prices, customerContainer);
		++totalFlowersBought;

	}

	return flowerCost;
}



int main(int argc, char ** argv)
{
	int flowers;
	int friends;
	PriceContainer priceFlower;

	// read input data
	scanf("%d %d\n", &flowers, &friends);
	// printf("Friends,Flowers\n%d %d\n", friends, flowers);	
	ReadFlowers(priceFlower, flowers);
	// PrintFlowers(priceFlower);

	// preprocess the data
	// sort with price as key
	PreprocessFlowers(priceFlower);
	printf("%d\n", CalculateCost(priceFlower, flowers, friends));

	return 0;
}