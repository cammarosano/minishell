# libft
Contains functions from:
- the original **libft** project (list functions included)
- **get_next_line** (multiple fd's feature not included - but available in the sources)
- **ft_printf** (all bonus conversions and flags included)
- additional functions:
	- ft_atoi_mv_ptr (char * pointer is moved to character after last digit)
	- ft_atof (text to float)
	- ft_atof_mv_ptr
	- ft_split_charset (takes more than one possible separator)
	- ft_free_split.c (clears memory allocated by ft_split and ft_split_charset)
	- ft_isspace (check if whitespace - man 3 isspace)
	- ft_lltoa: long long to string (decimal base).
	- ft_strcmp
	- ft_utoa_base: unsigned long long to string in any base.
	- ft_wchar_to_mb: wide char (Unicode code point) to multi-byte sequence (UTF-8)

Usage:\
 `make all clean`
