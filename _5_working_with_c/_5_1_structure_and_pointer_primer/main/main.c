#include <stdio.h>
#include <string.h>


typedef struct Person_struct {
  char firstName[20];
  char lastName[20];
  int age; 
} Person;

void updatePerson(Person  *person,  //< struct pointer
   char* fname,   //< char pointer - string literal
    char* lname,  //< char pointer - string literal
     int age      //< integer
    ) 
{
  strcpy(person->firstName, fname);
  strcpy(person->lastName, lname);
  person->age = age;
}
void exclamIt(char * phrase){
  strcat(phrase, "!");
}
void app_main(void)
{
  Person person;
  char phrase[20] ={"Hello world"}; //< string variable char []
  char* fname = "Augusto";          //< string literal char*
  char* lname = "Cavalcanti";

  // put exclamation point 
  exclamIt(phrase);
  printf("function output: %s\n", phrase);

  // initialize struct person
  updatePerson(&person,fname,lname,66); //< fname e lname are pointers
  printf("person: %s %s is %d years old\n", person.firstName, person.lastName, person.age);
}
