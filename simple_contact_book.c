#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define  MAX_PHONE_LENGTH 13
#define  MAX_MAIL_LENGTH 50
static int num_contacts = 0;

typedef struct {
	char name[MAX_NAME_LENGTH];
	char phone_number[MAX_PHONE_LENGTH];
	char mail[MAX_MAIL_LENGTH];
} Contact;

Contact * read_contact_file() {
	FILE *file;
	Contact *contact_book = NULL;
	file = fopen("contact_book.txt", "r"); // Opening the file
	if (file == NULL) {
		printf("Errore nella lettura del file Contatti.\n");
		return 0;
	}

	char name[MAX_NAME_LENGTH];
	char phone_number[MAX_PHONE_LENGTH];
	char mail[MAX_MAIL_LENGTH];
	while (fscanf(file, "%19[^,],%12[^,],%49[^\n]\n", name, phone_number, mail) == 3) {
		printf("%s,%s,%s\n", name, phone_number, mail);
		if (num_contacts == 0) {
			contact_book = (Contact *)malloc(sizeof(Contact)); // Allocation of memory for first element
		} else {
			Contact *new_book = (Contact *)realloc(contact_book, (num_contacts + 1) * sizeof(Contact)); // Resize memory for x elements
			if (new_book == NULL) {
				printf("Allocazione memoria non riuscita.\n");
				return 0;
			}
			contact_book = new_book;
		}

		if (contact_book == NULL) {
			printf("Allocazione memoria non riuscita.\n");
			return 0;
		} else {
			// Populating the struct
			strcpy(contact_book[num_contacts].name, name);
			strcpy(contact_book[num_contacts].phone_number, phone_number);
            strcpy(contact_book[num_contacts].mail, mail);
			num_contacts++;
		}
	}
	
	fclose(file); // Closing the file

	return contact_book;
}

int write_contact_file(Contact *contact_book) {
	FILE *file;
	file = fopen("contact_book.txt", "w"); // Opening the file
	if (file == NULL) {
		printf("Errore nella scrittura del file Contatti.\n");
		return 1;
	}

	for (int i = 0; i < num_contacts; i++) {
		fprintf(file, "%s,%s,%s\n", contact_book[i].name, contact_book[i].phone_number, contact_book[i].mail);
	}

	fclose(file);

	return 0;
}

Contact * add_contact(Contact *contact_book) {
	if (num_contacts == 0) {
		contact_book = (Contact *)malloc(sizeof(Contact)); // Allocation of memory for first element
	} else {
		Contact *new_book = (Contact *)realloc(contact_book, (num_contacts + 1) * sizeof(Contact)); // Resize memory for x elements
		if (new_book == NULL) {
			printf("Allocazione memoria non riuscita.\n");
			return 0;
		}
		contact_book = new_book;
	}

	if (contact_book == NULL) {
		printf("Allocazione memoria non riuscita.\n");
		return 0;
	} else {
		// Ask for contact information
		printf("Inserisci il nome: ");
		scanf("%19s", contact_book[num_contacts].name);
		printf("Inserisci il numero di telefono: ");
		scanf("%12s", contact_book[num_contacts].phone_number);
		printf("Inserisci la mail: ");
		scanf("%19s", contact_book[num_contacts].mail);
		num_contacts++;
	}

	return contact_book;
}

void view_contacts(Contact *contact_book) {
	printf("\nLista Contatti:\n");
	for (int i = 0; i < num_contacts; i++) {
		printf("%d) Nome: %s | N. Tel.: %s | Mail: %s\n", i + 1, contact_book[i].name, contact_book[i].phone_number, contact_book[i].mail);
	}
}

Contact * edit_contact(Contact *contact_book) {
	static int contact_to_edit;
	printf("Scegli il numero del contatto da modificare: ");
	scanf("%d", &contact_to_edit);
	
	if (contact_to_edit > 0 && contact_to_edit <= num_contacts) {
		// Ask for contact information
		printf("Modifica il nome: (%s) ", contact_book[contact_to_edit - 1].name);
		scanf("%20s", contact_book[contact_to_edit - 1].name);
		printf("Modifica il numero di telefono: (%s) ", contact_book[contact_to_edit - 1].phone_number);
		scanf("%13s", contact_book[contact_to_edit - 1].phone_number);
		printf("Modifica la mail: (%s) ", contact_book[contact_to_edit - 1].mail);
		scanf("%20s", contact_book[contact_to_edit - 1].mail);
	} else {
		printf("Numero non valido.\n");
		return 0;
	}

	return contact_book;
}

Contact * delete_contact(Contact *contact_book) {
	static int contact_to_delete;
	printf("Scegli il numero del contatto da eliminare: ");
	scanf("%d", &contact_to_delete);

	if (contact_to_delete > 0 && contact_to_delete <= num_contacts) {
		for (int i = contact_to_delete - 1; i < num_contacts - 1; i++) {
			contact_book[i] = contact_book[i + 1];
		}
		num_contacts--;
	}

	return contact_book;
}

int main() {
	Contact *contact_book = NULL;
	char input;
	contact_book = read_contact_file();

	do {
		printf("\nCosa vuoi fare?\n");
		printf("1 - Aggiungere un Contatto\n");
		printf("2 - Lista Contatti\n");
		printf("3 - Modifica un Contatto\n");
		printf("4 - Elimina un Contatto\n");
		printf("q - Esci\n");
		scanf(" %c", &input);

		switch (input) {
			case '1':
				contact_book = add_contact(contact_book);
				break;

			case '2':
				view_contacts(contact_book);
				break;

			case '3':
				contact_book = edit_contact(contact_book);
				break;

			case '4':
				contact_book = delete_contact(contact_book);
				break;

			case 'q':
				break;
		
			default:
				printf("Scelta non valida.\n");
				break;
		}
	}
	while (input != 'q');

	write_contact_file(contact_book);
	free(contact_book); // Free memory at end program

	return 0;
}