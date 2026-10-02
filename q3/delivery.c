#include <stdio.h>

/* Adds up all the distances with a loop */
int total_distance(int distances[], int count)
{
	int total;
	int i;

	total = 0;
	for (i = 0; i < count; i++)
	{
		total = total + distances[i];
	}

	return total;
}

/* Average = total / number of routes. It reuses total_distance(). */
float average_distance(int distances[], int count)
{
	int total;
	float average;

	total = total_distance(distances, count);
	average = (float)total / count;

	return average;
}

/* Finds the biggest distance in the array */
int longest_route(int distances[], int count)
{
	int longest;
	int i;

	longest = distances[0];
	for (i = 1; i < count; i++)
	{
		if (distances[i] > longest)
		{
			longest = distances[i];
		}
	}

	return longest;
}

/* Counts how many routes are longer than the limit */
int count_above_limit(int distances[], int count, int limit)
{
	int number;
	int i;

	number = 0;
	for (i = 0; i < count; i++)
	{
		if (distances[i] > limit)
		{
			number = number + 1;
		}
	}

	return number;
}

/* Adds up the distances using recursion (the function calls itself) */
int recursive_sum(int distances[], int count)
{
	/* base case: no routes left, so the sum is 0 */
	if (count == 0)
	{
		return 0;
	}

	/* last distance + the sum of all the routes before it */
	return distances[count - 1] + recursive_sum(distances, count - 1);
}

int main(void)
{
	int distances[100];
	int count;
	int limit;
	int i;

	printf("Enter number of routes: ");
	scanf("%d", &count);

	/* the array has room for 100 routes, and we need at least 1 */
	if (count < 1 || count > 100)
	{
		printf("Number of routes must be between 1 and 100.\n");
		return 1;
	}

	for (i = 0; i < count; i++)
	{
		printf("Enter distance %d: ", i + 1);
		scanf("%d", &distances[i]);
	}

	printf("Enter distance limit: ");
	scanf("%d", &limit);

	printf("\n===== DELIVERY DISTANCE ANALYSIS =====\n\n");
	printf("Total distance: %d km\n", total_distance(distances, count));
	printf("Average distance: %.2f km\n", average_distance(distances, count));
	printf("Longest route: %d km\n", longest_route(distances, count));
	printf("Routes above %d km: %d\n", limit, count_above_limit(distances, count, limit));
	printf("\nRecursive sum: %d km\n", recursive_sum(distances, count));

	return 0;
}
