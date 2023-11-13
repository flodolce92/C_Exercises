#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TASK_NAME 20

typedef struct {
	char task_name[MAX_TASK_NAME];
	bool completed;
} Task;

int main() {
	Task *todo_list = NULL; // Declare a pointer to Task struct
	char input = 'c';
	int num_tasks = 0;

	while (input != 'q') {
		printf("\nCosa vuoi fare?\n");
		printf("1 - Aggiungere Task\n");
		printf("2 - Vedere la lista\n");
		printf("3 - Segna completamento\n");
		printf("4 - Elimina task complete\n");
		printf("q - Esci\n");
		scanf(" %c", &input);

		switch (input) {
			case '1':
				if (num_tasks == 0) {
					todo_list = (Task *)malloc(sizeof(Task)); // Allocate memory for the first task
				} else {
					Task *new_list = (Task *)realloc(todo_list, (num_tasks + 1) * sizeof(Task)); // Resize memory for additional tasks
					if (new_list == NULL) {
						printf("Allocazione memoria non riuscita\n");
						break;
					}
					todo_list = new_list;
				}

				if (todo_list == NULL) {
					printf("Allocazione memoria non riuscita\n");
				} else {
					printf("Inserisci il nome della task: ");
					scanf("%19s", todo_list[num_tasks].task_name);
					todo_list[num_tasks].completed = false;
					num_tasks++;
				}
				break;
		
			case '2':
				printf("\nTodo List:\n");
				for (int i = 0; i < num_tasks; i++) {
					printf("%d) Nome: %s | %s\n", i + 1, todo_list[i].task_name, todo_list[i].completed ? "Completata" : "Non Completata");
				}
				break;

			case '3':
				printf("Scegli il numero della task da segnare completa: ");
				int task_to_mark;
				scanf("%d", &task_to_mark);

				if (task_to_mark > 0 && task_to_mark <= num_tasks) {
					todo_list[task_to_mark - 1].completed = true;
				} else {
					printf("Task non valida.\n");
				}
				break;

			case '4': {
				int originalNumTasks = num_tasks;
				num_tasks = 0;

				for (int i = 0; i < originalNumTasks; i++) {
					if (todo_list[i].completed != true) {
						todo_list[num_tasks] = todo_list[i];
						num_tasks++;
					}
				}
			break;
			}

			case 'q':
				break;
			
			default:
				printf("Scelta non valida.\n");
				break;
		}
	}

	free(todo_list); // Free allocated memory before exiting

	return 0;
}