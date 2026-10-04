#include <stdio.h>

/* Returns how far the temperature is from 25 C. The answer is never negative. */
float temperature_deviation(float temperature)
{
	float deviation;

	deviation = temperature - 25;

	/* if the difference is negative, make it positive */
	if (deviation < 0)
	{
		deviation = -deviation;
	}

	return deviation;
}

/* Calculates the water-quality index from the two sensor readings */
float quality_index(float temperature, float turbidity)
{
	float deviation;
	float penalty;
	float index;

	deviation = temperature_deviation(temperature);
	penalty = turbidity / 2;
	index = 100 - (deviation + penalty);

	return index;
}

/* Prints Good, Warning or Critical depending on the index */
void print_status(float index)
{
	if (index >= 80)
	{
		printf("Status        : Good\n");
	}
	else if (index >= 60)
	{
		printf("Status        : Warning\n");
	}
	else
	{
		printf("Status        : Critical\n");
	}
}

int main(void)
{
	float temperature;
	float turbidity;
	float index;

	/* read the two sensor values */
	printf("Enter temperature (C): ");
	scanf("%f", &temperature);
	printf("Enter turbidity (NTU): ");
	scanf("%f", &turbidity);

	/* calculate the index */
	index = quality_index(temperature, turbidity);

	/* print the report */
	printf("\n===== WATER QUALITY REPORT =====\n");
	printf("Temperature   : %.2f C\n", temperature);
	printf("Turbidity     : %.2f NTU\n", turbidity);
	printf("Quality index : %.2f\n", index);
	print_status(index);
	printf("================================\n");

	return 0;
}
