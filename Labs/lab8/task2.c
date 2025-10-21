#include <stdio.h>
#include <string.h>

double to_c(double x, char c){
    switch(c){
        case 'C': return x;
        case 'F': return (x - 32.0) * (5.0/9.0);
        case 'K': return x - 273.15;
    }
}

double from_c(double x, char c){
    switch(c){
        case 'C': return x;
        case 'F': return x * (9.0/5.0) + 32.0;
        case 'K': return x + 273.15;
    }
}

int main() {
    double value;
    char og_scale;
    char new_scale;
    printf("Enter the temperature value: ");
    scanf("%lf", &value);
    getchar();

    printf("Enter the original scale (C, F, or K): ");
    scanf(" %c", &og_scale);

    printf("Enter the scale to convert (C, F, or K): ");
    scanf(" %c", &new_scale);

    value = to_c(value, og_scale);
    double stored_c = value;
    value = from_c(value, new_scale);

    char category[50];
    char advisory[100];

    if (stored_c < 0){
        strcpy(category, "Freezing");
        strcpy(advisory, "Stay indoors!");
    }
    else if (stored_c <10){
        strcpy(category, "Cold");
        strcpy(advisory, "Drink something warm!");
    }
    else if (stored_c < 25){
        strcpy(category, "Comfortable");
        strcpy(advisory, "Go have fun!");
    }
    else if(stored_c <35){
        strcpy(category, "Hot");
        strcpy(advisory, "Cool off in the pool!");
    }
    else{
        strcpy(category, "Extreme Heat");
        strcpy(advisory, "Do not go outside!");
    }

    printf("Converted temperature: %.2lf\n", value);
    printf("Temperature category: %s\n", category);
    printf("Weather advisory: %s\n", advisory);


    
    return 0;
}

