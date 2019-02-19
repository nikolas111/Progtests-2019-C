#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TCar {
    struct TCar *m_Next;
    char *m_Model;
} TCAR;

typedef struct TEmployee {
    struct TEmployee *m_Next;
    struct TCar *m_Car;
    char *m_Name;
} TEMPLOYEE;

typedef struct TOffice {
    TEMPLOYEE *m_Emp;
    TCAR *m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */



TOFFICE *initOffice() {
    TOFFICE *new_structure = (TOFFICE *) malloc(sizeof(TOFFICE));
    new_structure->m_Emp = NULL;
    new_structure->m_Car = NULL;
    return new_structure;
}
void addEmployee(TOFFICE *office, const char *name) {
    TEMPLOYEE *new_employee = (TEMPLOYEE *) calloc(1, sizeof(TEMPLOYEE));
    new_employee->m_Car = NULL;
    long unsigned int size = strlen(name) + 1;
    new_employee->m_Name = (char *) calloc(size, sizeof(char));
    strncpy(new_employee->m_Name, name, size);
    new_employee->m_Next = office->m_Emp;
    office->m_Emp = new_employee;
}
void addCar(TOFFICE *office, const char *model) {
    TCAR *new_car = (TCAR *) calloc(1, sizeof(TCAR));
    long unsigned int size = strlen(model) + 1;
    new_car->m_Model = (char *) calloc(size, sizeof(char));
    strncpy(new_car->m_Model, model, size);
    new_car->m_Next = office->m_Car;
    office->m_Car = new_car;
}
void CAR_CLONE(TOFFICE *office, TOFFICE *new_office) {
    TCAR *pt_cars = office->m_Car;
    TCAR *last_car=NULL; 
    TCAR *head_car = (TCAR *) malloc(sizeof(TCAR));
    head_car->m_Model = (char *) malloc((strlen(office->m_Car->m_Model) + 1) * sizeof(char));
    strncpy(head_car->m_Model, office->m_Car->m_Model, strlen(office->m_Car->m_Model) + 1);
    head_car->m_Next = NULL;
    new_office->m_Car = head_car;
    last_car = head_car;
    pt_cars = pt_cars->m_Next;

    while (pt_cars) {
        TCAR *new_car = (TCAR *) malloc(sizeof(TCAR));
        new_car->m_Model = (char *) malloc((strlen(pt_cars->m_Model) + 1) * sizeof(char));

        strncpy(new_car->m_Model, pt_cars->m_Model, strlen(pt_cars->m_Model) + 1);
        new_car->m_Next = NULL;
        last_car->m_Next = new_car;
        last_car = last_car->m_Next;
        pt_cars = pt_cars->m_Next;
    }
}

TCAR *REFERENCE_SEARCHER(TOFFICE *office, TCAR *reference, TOFFICE *new_office) {
    TCAR *searcher = office->m_Car;
    int position = 0;
    while (searcher != reference) {
        ++position;
        searcher = searcher->m_Next;
    }
    searcher = new_office->m_Car;
    for (int j = 0; j < position; ++j) {
        searcher = searcher->m_Next;
    }
    return searcher;
}
void EMPLOYEE_CLONE(TOFFICE *office, TOFFICE *new_office) {
    TEMPLOYEE *pt_emes = office->m_Emp;
    TEMPLOYEE *last_employee;
    TEMPLOYEE *head_employee = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
    head_employee->m_Name = (char *) malloc((strlen(office->m_Emp->m_Name) + 1) * sizeof(char));
    strncpy(head_employee->m_Name, office->m_Emp->m_Name, strlen(office->m_Emp->m_Name) + 1);
    head_employee->m_Next = NULL;
    new_office->m_Emp = head_employee;
    head_employee->m_Car=NULL;
    //If office-m_Emp is not null then there  has  to be already a car 
    if(office->m_Emp->m_Car)
      head_employee->m_Car=REFERENCE_SEARCHER(office,office->m_Emp->m_Car,new_office);
    last_employee = head_employee;
    pt_emes = pt_emes->m_Next;
    while (pt_emes) {
        TEMPLOYEE *new_employee = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
        new_employee->m_Name = (char *) malloc((strlen(pt_emes->m_Name) + 1) * sizeof(char));
        strncpy(new_employee->m_Name, pt_emes->m_Name, strlen(pt_emes->m_Name) + 1);
        new_employee->m_Next = NULL;
        new_employee->m_Car = NULL;
        last_employee->m_Next = new_employee;
        last_employee = last_employee->m_Next;
        if (pt_emes->m_Car) {
            new_employee->m_Car = REFERENCE_SEARCHER(office, pt_emes->m_Car, new_office);
        }
        pt_emes = pt_emes->m_Next;
    }
}
TOFFICE *cloneOffice(TOFFICE *office) {
    if (office != NULL ) {
        TOFFICE *new_office = initOffice();
        if(office->m_Car!=NULL)
        {
            CAR_CLONE(office, new_office);
        }
        if(office->m_Emp != NULL)
        {
            EMPLOYEE_CLONE(office, new_office);
        }
        return new_office;
    } else return NULL;
}
void freeOffice(TOFFICE *office) {
    TCAR *CAR;
    TEMPLOYEE *EMPLOYEE;
    if (office != NULL) {
        while (office->m_Car != NULL) {
            CAR = office->m_Car;
            office->m_Car = office->m_Car->m_Next;
            free(CAR->m_Model);
            free(CAR);
        }
        while (office->m_Emp != NULL) {
            EMPLOYEE = office->m_Emp;
            office->m_Emp = office->m_Emp->m_Next;
            free(EMPLOYEE->m_Name);
            free(EMPLOYEE);
        }
    }
    free(office);
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TOFFICE *a, *b;
    char tmp[100];

    assert (sizeof(TOFFICE) == 2 * sizeof(void *));
    assert (sizeof(TEMPLOYEE) == 3 * sizeof(void *));
    assert (sizeof(TCAR) == 2 * sizeof(void *));
    a = initOffice ();
    addEmployee ( a, "Peter" );
    addEmployee ( a, "John" );
    addEmployee ( a, "Joe" );
    addEmployee ( a, "Maria" );
    addCar ( a, "Skoda Octavia" );
    addCar ( a, "VW Golf" );
    a -> m_Emp -> m_Car = a -> m_Car;
    a -> m_Emp -> m_Next -> m_Next -> m_Car = a -> m_Car -> m_Next;
    a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = a -> m_Car;
    assert ( a -> m_Emp
             && ! strcmp ( a -> m_Emp -> m_Name, "Maria" )
             && a -> m_Emp -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Joe" )
             && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
             && ! strcmp ( a -> m_Car -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next == NULL );
    b = cloneOffice ( a );
    strncpy ( tmp, "Moe", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Victoria", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Peter", sizeof ( tmp ) );
    addEmployee ( a, tmp );
    strncpy ( tmp, "Citroen C4", sizeof ( tmp ) );
    addCar ( a, tmp );
    b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = b -> m_Car -> m_Next -> m_Next;
    assert ( a -> m_Emp
             && ! strcmp ( a -> m_Emp -> m_Name, "Peter" )
             && a -> m_Emp -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Victoria" )
             && a -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "Moe" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
    assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( a -> m_Car
             && ! strcmp ( a -> m_Car -> m_Model, "Citroen C4" ) );
    assert ( a -> m_Car -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "VW Golf" ) );
    assert ( a -> m_Car -> m_Next -> m_Next
             && ! strcmp ( a -> m_Car -> m_Next -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( a -> m_Car -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b -> m_Emp
             && ! strcmp ( b -> m_Emp -> m_Name, "Maria" )
             && b -> m_Emp -> m_Car == b -> m_Car );
    assert ( b -> m_Emp -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Name, "Joe" )
             && b -> m_Emp -> m_Next -> m_Car == NULL );
    assert ( b -> m_Emp -> m_Next -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
             && b -> m_Emp -> m_Next -> m_Next -> m_Car == b -> m_Car -> m_Next );
    assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next
             && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
             && b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
    assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b -> m_Car
             && ! strcmp ( b -> m_Car -> m_Model, "VW Golf" ) );
    assert ( b -> m_Car -> m_Next
             && ! strcmp ( b -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
    assert ( b -> m_Car -> m_Next -> m_Next == NULL );
    freeOffice ( a );
    freeOffice ( b );


    return 0;

}

#endif /* __PROGTEST__ */
