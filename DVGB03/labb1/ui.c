#include "ui.h"
#include "io.h"
#include "analyze.h"

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//
// Private
//
static void ui_invalid_input()
{
	printf("info> bad input\n");
}

static void ui_exit()
{
	printf("info> bye\n");
}

static char ui_get_choice()
{
	char buf[3];
	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n)
{
	while (n-- > 0)
	{
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options)
{
	int i;

	for (i = 0; i < num_options; i++)
	{
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}

static void ui_menu()
{
	const char *options[] = {
		"Menu",
		"Exit\n",
		"Bubble sort best case",
		"Bubble sort worst case",
		"Bubble sort average case\n",
		"Insertion sort best case",
		"Insertion sort worst case",
		"Insertion sort average case\n",
		"Quick sort best case",
		"Quick sort worst case",
		"Quick sort average case\n",
		"Linear search best case",
		"Linear search worst case",
		"Linear search average case\n",
		"Binary search best case",
		"Binary search worst case",
		"Binary search average case",
	};

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

void print_result(result_t *buf, char *algorithm, char *case_)
{
	ui_line('*', MENU_WIDTH);
	printf("%25s: %s\n", algorithm, case_);
	ui_line('~', MENU_WIDTH);
	printf("size       time T(s)   T/n         T/logn       T/nlogn       T/n2\n");
	ui_line('~', MENU_WIDTH);

	for (int i = 0; i < RESULT_ROWS; i++)
	{
		printf("size:%5d %.9f %.9f %.9f %.9f %.9f\n",
			   buf[i].size,
			   buf[i].time,
			   buf[i].time / buf[i].size,
			   buf[i].time / log(buf[i].size),
			   buf[i].time / (buf[i].size * log(buf[i].size)),
			   buf[i].time / pow(buf[i].size, 2));
	}

	return;
}

//
// Public
//
#define ASCII_MENU_OFFSET 99
void ui_run()
{
	bool running;
	result_t result[RESULT_ROWS];
	ui_menu();
	running = true;
	while (running)
	{
		char choice = ui_get_choice();
		switch (choice)
		{
		case 'a':
			ui_menu();
			break;
		case 'b':
			running = false;
			break;
		case 'c':
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
			print_result(result, "bubble sort", "best");
			break;
		case 'd':
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
			print_result(result, "bubble sort", "worst");
			break;
		case 'e':
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
			print_result(result, "bubble sort", "average");
			break;
		case 'f':
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
			print_result(result, "insertion sort", "best");
			break;
		case 'g':
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
			print_result(result, "insertion sort", "worst");
			break;
		case 'h':
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
			print_result(result, "insertion sort", "average");
			break;
		case 'i':
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
			print_result(result, "quick sort", "best");
			break;
		case 'j':
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
			print_result(result, "quick sort", "worst");
			break;
		case 'k':
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
			print_result(result, "quick sort", "average");
			break;
		case 'l':
			benchmark(linear_search_t, best_t, result, RESULT_ROWS);
			print_result(result, "linear search", "best");
			break;
		case 'm':
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
			print_result(result, "linear search", "worst");
			break;
		case 'n':
			benchmark(linear_search_t, average_t, result, RESULT_ROWS);
			print_result(result, "linear search", "average");
			break;
		case 'o':
			benchmark(binary_search_t, best_t, result, RESULT_ROWS);
			print_result(result, "binary search", "best");
			break;
		case 'p':
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
			print_result(result, "binary search", "worst");
			break;
		case 'q':
			benchmark(binary_search_t, average_t, result, RESULT_ROWS);
			print_result(result, "binary search", "average");
			break;
		default:
			ui_invalid_input();
			break;
		}
	}
	ui_exit();
}
