#include <iostream>

using namespace std;

int main()
{
    int size, element;
    
    cout<<"Input matrix size = "; 
    cin>>size;
    
    int matrix[size][size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            cout<<"Input element matrix = ";
            cin>>element;
            matrix[i][j] = element;
         }
    }

    for (int i = 0; i< size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout.width(2);
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    
    
    
    int sum;    
    int *mat = &matrix[size-1][size-1];// Ssilka na last element элемент матрицы

    asm(
            "mov %[mat], %%rsi;"// V rsi cladem ssilke na last element
            "movl %[size], %%r8d;"// r8 kak shag i tok ot size-1 do 0
            "dec %%r8d;"
            "xorl %%edx, %%edx;"// Obiyavim summu kotoraya budet poschitana
            

        "i:" // Loop i
            // Initial j
            "movl %[size], %%r9d;"
            "dec %%r9d;"
        
        "j:" //Loop j
            // Check main diagonal
            "cmpl %%r9d, %%r8d;"
            "je sum;"

            // Podhodit ? good : propuskaem summirovanit 
            "jmp end_sum;"

        // Summirovanie
        "sum:"
            // Berem element matrix
            "movl (%%rsi), %%ebx;"
            // Sum+=sum
            "addl %%ebx, %%edx;"
            
        // Check na end stroki
        "end_sum:"
            // j-=1
            "dec %%r9d;"
            // Peremeshaem ukazatel nazad <-
            "sub $4, %%rsi;"
            // j ne ushel za massiv?
            "cmpl $-1, %%r9d;"
            // Repeat loop j
            "jne j;"

            // Tozhe samoe tok dlya i
            "dec %%r8d;"
            "cmpl $-1, %%r8d;"
            "jne i;"

            // Zapisivaem summ iz vsavki v peremenuyu "sum"
            "movl %%edx, %[sum];"
            :
            :[mat]"m"(mat), [size]"m"(size), [sum]"m"(sum)
            :
       );

   
    cout << " Sum diagonal = " << sum << endl;

    return 0;
}
