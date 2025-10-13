#include <stdio.h>
#include <stdlib.h>



//struct
struct rec{
    int id;
    int val;
    char name[100];
};





//massivchik
void print_recs(struct rec *a, int n){

    int i;
    printf(" # | id | val | name\n");
    printf("-------------------------------\n");

    for (i = 0; i < n; i++){

        printf("%2d | %2d | %3d | %s\n", i + 1, a[i].id, a[i].val, a[i].name);
    }
    printf("\n");
}




// bubble sortik

void sort_by_val(struct rec *a, int n){
    
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++){
            if (a[j].val > a[j + 1].val){
                struct rec t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}








int main(void){


    int n, i;
    struct rec a[100];  //max 100



    printf("kol-vo strok (1..100)???: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) return 0;




    printf("vvedi %d strok: id val name (name = odno_slovo)\n", n); //uznaem skolko strok nado vvesti

    for (i = 0; i < n; i++){

        printf("#%d: ", i + 1); 
        scanf("%d%d%99s", &a[i].id, &a[i].val, a[i].name); //vivodim na ekran chto vveli
    }




    puts("do MEGA sort:");
    print_recs(a, n);

    sort_by_val(a, n);

    puts("posle MEGA sort:");
    print_recs(a, n);



    return 0;

}


