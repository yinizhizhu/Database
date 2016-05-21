#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getEmployee()
{
    int i=0, j;
    float salary = 1000;
    char location[57][15];
    char nameB[57][15];
    char ssn[19] = "1111111111111111";
    FILE* name = fopen("name.txt", "r");
    FILE* loc = fopen("location.txt", "r");
    FILE* out = fopen("employee.txt", "w");
    while (fscanf(loc, "%s", location[i]) == 1 && fscanf(name, "%s", nameB[i]) == 1)
    {
        printf("%d: %s-->", strlen(location[i]), location[i]);
        printf("%d: %s, name\n", strlen(nameB[i]), nameB[i]);
        if (i > 9)
            fprintf(out, "%s\t%s%d\t%s\t%0.2f\t%s0%d\t%d\n", nameB[i], ssn, i, location[i], salary, ssn, i%10, i%5+1);
        else
            fprintf(out, "%s\t%s0%d\t%s\t%0.2f\t%s0%d\t%d\n", nameB[i], ssn, i, location[i], salary, ssn, (i+12)%10, i%5+1);
        i++;
        salary += 10;
    }
    fclose(out);
    fclose(loc);
    fclose(name);
    return;
}

int main()
{
    getEmployee();
    return 0;
}
