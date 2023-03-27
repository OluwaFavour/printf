#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * print_char - prints a character
 * @args: the character to print
 * @written: the number of characters printed
 */
void print_char(va_list args, int *written)
{
	char c = (char)va_arg(args, int);

	_putchar(c);
	*written += 1;
}

/**
 * print_string - prints a string
 * @args: the string to print
 * @written: the number of characters printed
 */
void print_string(va_list args, int *written)
{
	char *s = va_arg(args, char *);

	while (*s != '\0')
	{
		_putchar(s);
		s++;
		*written += 1;
	}
}

/**
 * print_percent - prints a percent sign
 * @written: the number of characters printed
 */
void print_percent(int *written)
{
	_putchar(37); /* print "%" */
	*written += 1;
}

/**
 * print_invalid - prints an invalid conversion specifier
 * @format: the format string
 * @written: the number of characters printed
 */
void print_invalid(const char *format, int *written)
{
	write(STDOUT_FILENO, format - 1, 2);
	*written += 2;
}

/**
 * handle_conversion_specifier - handles a conversion specifier
 * @format_ptr: the format string
 * @args: the list of arguments
 * @written: the number of characters printed
 */
void handle_conversion_specifier(const char **format_ptr,
		va_list args,
		int *written
)
{
	char conversion_specifier = *(*format_ptr)++;
	switch (conversion_specifier)
	{
	case 'c':
	{
		print_char(args, written);
		break;
	}
	case 's':
	{
		print_string(args, written);
		break;
	}
	case '%':
	{
		print_percent(written);
		break;
	}
	default:
	{
		print_invalid(*format_ptr, written);
		break;
	}
	}
}

/**
 * _printf - prints a formatted string
 * @format: the format string
 * Return: the number of characters printed
 */
int _printf(const char *format, ...)i
{
	va_list args;
	int written = 0;

	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			handle_conversion_specifier(&format, args, &written);
		}
		else
		{
			_putchar(format);
			written++;
		}
		format++;
	}
	va_end(args);
	return (written);
}
