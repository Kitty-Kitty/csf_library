



#include <stdarg.h>
#include "prot_gmp_std.h"
#include "prot_gmp_string.h"







/*
 * supported formats:
 *    %[0][width][x][X]O        off_t
 *    %[0][width]T              time_t
 *    %[0][width][u][x|X]z      ssize_t/size_t
 *    %[0][width][u][x|X]d      int/gm_std_uint
 *    %[0][width][u][x|X]l      long
 *    %[0][width|m][u][x|X]i    gmp_int_t/gmp_uint_t
 *    %[0][width][u][x|X]D      gm_std_uint/gm_std_uint
 *    %[0][width][u][x|X]L      gm_std_int64/gm_std_uint64
 *    %[0][width|m][u][x|X]A    gmp_atomic_int_t/gmp_atomic_uint_t
 *    %[0][width][.width]f      double, max valid number fits to %18.15f
 *    %P                        gmp_pid_t
 *    %M                        gmp_msec_t
 *    %r                        rlim_t
 *    %p                        gm_std_void *
 *    %V                        gmp_str_t *
 *    %v                        gmp_variable_value_t *
 *    %s                        null-terminated string
 *    %*s                       length and string
 *    %Z                        '\0'
 *    %N                        '\n'
 *    %c                        gm_std_char
 *    %%                        %
 *
 *
 * supported gmdt formats:
 *	  %[0][width][x][X]G		gmdt formats
 *
 *
 *  reserved:
 *    %t                        ptrdiff_t
 *    %S                        null-terminated wchar string
 *    %C                        wchar
 */


gm_std_uchar * gmp_cdecl
gmp_sprintf(gm_std_uchar *buf, const gm_std_char *fmt, ...)
{
    gm_std_uchar	*p;
    va_list			args;

    va_start(args, fmt);
    p = gmp_vslprintf(buf, (gm_std_uchar*) -1, fmt, args);
    va_end(args);

    return p;
}



/*
 * supported formats:
 *    %[0][width][x][X]O        off_t
 *    %[0][width]T              time_t
 *    %[0][width][u][x|X]z      ssize_t/size_t
 *    %[0][width][u][x|X]d      int/gm_std_uint
 *    %[0][width][u][x|X]l      long
 *    %[0][width|m][u][x|X]i    gmp_int_t/gmp_uint_t
 *    %[0][width][u][x|X]D      gm_std_uint/gm_std_uint
 *    %[0][width][u][x|X]L      gm_std_int64/gm_std_uint64
 *    %[0][width|m][u][x|X]A    gmp_atomic_int_t/gmp_atomic_uint_t
 *    %[0][width][.width]f      double, max valid number fits to %18.15f
 *    %P                        gmp_pid_t
 *    %M                        gmp_msec_t
 *    %r                        rlim_t
 *    %p                        gm_std_void *
 *    %V                        gmp_str_t *
 *    %v                        gmp_variable_value_t *
 *    %s                        null-terminated string
 *    %*s                       length and string
 *    %Z                        '\0'
 *    %N                        '\n'
 *    %c                        gm_std_char
 *    %%                        %
 *
 *
 * supported gmdt formats:
 *	  %[0][width][x][X]G		gmdt formats
 *
 *
 *  reserved:
 *    %t                        ptrdiff_t
 *    %S                        null-terminated wchar string
 *    %C                        wchar
 */


gm_std_uchar * gmp_cdecl
gm_gmp_sprintf(gm_std_uchar *buf, const gm_std_char *fmt, ...)
{
    gm_std_uchar	*p;
    va_list			args;

    va_start(args, fmt);
    p = gm_gmp_vslprintf(buf, (gm_std_uchar*) -1, fmt, args);
    va_end(args);

    return p;
}


#if 0

gm_std_uchar * gmp_cdecl
gmp_snprintf(gm_std_uchar *buf, size_t max, const gm_std_char *fmt, ...)
{
    gm_std_uchar	*p;
    va_list			args;

    va_start(args, fmt);
    p = gmp_vslprintf(buf, buf + max, fmt, args);
    va_end(args);

    return p;
}


gm_std_uchar * gmp_cdecl
gmp_slprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, ...)
{
    gm_std_uchar	*p;
    va_list			args;




    va_start(args, fmt);
    p = gmp_vslprintf(buf, last, fmt, args);
    va_end(args);

    return p;
}

#endif


gm_std_uchar *
gmp_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, va_list args)
{
    gm_std_uchar                *p, zero;
    int							d;
    size_t						len, slen;
    gm_std_int64				i64;
    gm_std_uint64				ui64;
    gm_std_uint					width, sign, hex, max_width, frac_width;




    while (*fmt && buf < last) {

        /*
         * "buf < last" means that we could copy at least one character:
         * the plain character, "%%", "%c", and minus without the checking
         */

        if (*fmt == '%') {

            i64 = 0;
            ui64 = 0;

            zero = (gm_std_uchar) ((*++fmt == '0') ? '0' : ' ');
            width = 0;
            sign = 1;
            hex = 0;
            max_width = 0;
            frac_width = 0;
            slen = (size_t) -1;

            while (*fmt >= '0' && *fmt <= '9') {
                width = width * 10 + *fmt++ - '0';
            }


            for ( ;; ) {
                switch (*fmt) {

                case 'u':
                    sign = 0;
                    fmt++;
                    continue;

                case 'm':
                    max_width = 1;
                    fmt++;
                    continue;

                case 'X':
                    hex = 2;
                    sign = 0;
                    fmt++;
                    continue;

                case 'x':
                    hex = 1;
                    sign = 0;
                    fmt++;
                    continue;

                case '.':
                    fmt++;

                    while (*fmt >= '0' && *fmt <= '9') {
                        frac_width = frac_width * 10 + *fmt++ - '0';
                    }

                    break;

                case '*':
                    slen = va_arg(args, size_t);
                    fmt++;
                    continue;

                default:
                    break;
                }

                break;
            }


            switch (*fmt) {
            case 's':
                p = va_arg(args, gm_std_uchar *);

                if (slen == (size_t) -1) {
                    while (*p && buf < last) {
                        *buf++ = *p++;
                    }

                } else {
                    len = gmp_min(((size_t) (last - buf)), slen);
                    buf = gmp_std_cpymem(buf, p, len);
                }

                fmt++;

                continue;

            case 'T':
                i64 = (gm_std_int64) va_arg(args, time_t);
                sign = 1;
                break;

            case 'd':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, int);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_uint);
                }
                break;

            case 'l':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, long);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_ulong);
                }
                break;

            case 'D':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, gm_std_uint);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_uint);
                }
                break;

            case 'L':
                if (sign) {
                    i64 = va_arg(args, gm_std_int64);
                } else {
                    ui64 = va_arg(args, gm_std_uint64);
                }
                break;

			case 'c':
                d = va_arg(args, int);
                *buf++ = (gm_std_uchar) (d & 0xff);
                fmt++;

                continue;

            case 'Z':
                *buf++ = '\0';
                fmt++;

                continue;

            case 'N':
#if (NGX_WIN32)
                *buf++ = GM_SDT_CR;
#endif
                *buf++ = GM_SDT_LF;
                fmt++;

                continue;

            case '%':
                *buf++ = '%';
                fmt++;

                continue;

            default:
                *buf++ = *fmt++;

                continue;
            }

            if (sign) {
                if (i64 < 0) {
                    *buf++ = '-';
                    ui64 = (gm_std_uint64) -i64;

                } else {
                    ui64 = (gm_std_uint64) i64;
                }
            }

            buf = gmp_sprintf_num(buf, last, ui64, zero, hex, width);

            fmt++;

        } else {
            *buf++ = *fmt++;
        }
    }

    return buf;
}

gm_std_uchar *
gm_gmp_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, va_list args)
{
    gm_std_uchar                *p, zero;
    int							d;
    size_t						len, slen;
    gm_std_int64				i64;
    gm_std_uint64				ui64;
    gm_std_uint					width, sign, hex, max_width, frac_width;




    while (*fmt && buf < last) {

        /*
         * "buf < last" means that we could copy at least one character:
         * the plain character, "%%", "%c", and minus without the checking
         */

        if (*fmt == '%') {

            i64 = 0;
            ui64 = 0;

            zero = (gm_std_uchar) ((*++fmt == '0') ? '0' : ' ');
            width = 0;
            sign = 1;
            hex = 0;
            max_width = 0;
            frac_width = 0;
            slen = (size_t) -1;

            while (*fmt >= '0' && *fmt <= '9') {
                width = width * 10 + *fmt++ - '0';
            }


            for ( ;; ) {
                switch (*fmt) {

                case 'u':
                    sign = 0;
                    fmt++;
                    continue;

                case 'm':
                    max_width = 1;
                    fmt++;
                    continue;

                case 'X':
                    hex = 2;
                    sign = 0;
                    fmt++;
                    continue;

                case 'x':
                    hex = 1;
                    sign = 0;
                    fmt++;
                    continue;

                case '.':
                    fmt++;

                    while (*fmt >= '0' && *fmt <= '9') {
                        frac_width = frac_width * 10 + *fmt++ - '0';
                    }

                    break;

                case '*':
                    slen = va_arg(args, size_t);
                    fmt++;
                    continue;

                default:
                    break;
                }

                break;
            }


            switch (*fmt) {
            case 's':
                p = va_arg(args, gm_std_uchar *);

                if (slen == (size_t) -1) {
                    while (*p && buf < last) {
                        *buf++ = *p++;
                    }

                } else {
                    len = gmp_min(((size_t) (last - buf)), slen);
                    buf = gmp_std_cpymem(buf, p, len);
                }

                fmt++;

                continue;

            case 'T':
                i64 = (gm_std_int64) va_arg(args, time_t);
                sign = 1;
                break;

            case 'd':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, int);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_uint);
                }
                break;

            case 'l':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, long);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_ulong);
                }
                break;

            case 'D':
                if (sign) {
                    i64 = (gm_std_int64) va_arg(args, gm_std_uint);
                } else {
                    ui64 = (gm_std_uint64) va_arg(args, gm_std_uint);
                }
                break;

            case 'L':
                if (sign) {
                    i64 = va_arg(args, gm_std_int64);
                } else {
                    ui64 = va_arg(args, gm_std_uint64);
                }
                break;

			case 'c':
                d = va_arg(args, int);
                *buf++ = (gm_std_uchar) (d & 0xff);
                fmt++;

                continue;

            case 'Z':
                *buf++ = '\0';
                fmt++;

                continue;

            case 'N':
#if (NGX_WIN32)
                *buf++ = GM_SDT_CR;
#endif
                *buf++ = GM_SDT_LF;
                fmt++;

                continue;

            case '%':
                *buf++ = '%';
                fmt++;

                continue;

			case 'G':

				continue;
            default:
                *buf++ = *fmt++;

                continue;
            }

            if (sign) {
                if (i64 < 0) {
                    *buf++ = '-';
                    ui64 = (gm_std_uint64) -i64;

                } else {
                    ui64 = (gm_std_uint64) i64;
                }
            }

            buf = gmp_sprintf_num(buf, last, ui64, zero, hex, width);

            fmt++;

        } else {
            *buf++ = *fmt++;
        }
    }

    return buf;
}


static gm_std_uchar *
gmp_sprintf_num(gm_std_uchar *buf, gm_std_uchar *last, gm_std_uint64 ui64, gm_std_uchar zero,
    gm_std_uint hexadecimal, gm_std_uint width)
{
    gm_std_uchar         *p, temp[GM_SDT_INT64_LEN + 1];
                       /*
                        * we need temp[NGX_INT64_LEN] only,
                        * but icc issues the warning
                        */
    size_t					len;
    gm_std_uint				ui32;
    static gm_std_uchar		hex[] = "0123456789abcdef";
    static gm_std_uchar		HEX[] = "0123456789ABCDEF";





    p = temp + GM_SDT_INT64_LEN;

    if (hexadecimal == 0) {

        if (ui64 <= GM_SDT_MAX_UINT32_VALUE) {

            /*
             * To divide 64-bit numbers and to find remainders
             * on the x86 platform gcc and icc call the libc functions
             * [u]divdi3() and [u]moddi3(), they call another function
             * in its turn.  On FreeBSD it is the qdivrem() function,
             * its source code is about 170 lines of the code.
             * The glibc counterpart is about 150 lines of the code.
             *
             * For 32-bit numbers and some divisors gcc and icc use
             * a inlined multiplication and shifts.  For example,
             * unsigned "i32 / 10" is compiled to
             *
             *     (i32 * 0xCCCCCCCD) >> 35
             */

            ui32 = (gm_std_uint) ui64;

            do {
                *--p = (gm_std_uchar) (ui32 % 10 + '0');
            } while (ui32 /= 10);

        } else {
            do {
                *--p = (gm_std_uchar) (ui64 % 10 + '0');
            } while (ui64 /= 10);
        }

    } else if (hexadecimal == 1) {

        do {

            /* the "(gm_std_uint)" cast disables the BCC's warning */
            *--p = hex[(gm_std_uint) (ui64 & 0xf)];

        } while (ui64 >>= 4);

    } else { /* hexadecimal == 2 */

        do {

            /* the "(gm_std_uint)" cast disables the BCC's warning */
            *--p = HEX[(gm_std_uint) (ui64 & 0xf)];

        } while (ui64 >>= 4);
    }

    /* zero or space padding */

    len = (temp + GM_SDT_INT64_LEN) - p;

    while (len++ < width && buf < last) {
        *buf++ = zero;
    }

    /* number safe copy */

    len = (temp + GM_SDT_INT64_LEN) - p;

    if (buf + len > last) {
        len = last - buf;
    }

    return gmp_std_cpymem(buf, p, len);
}

gm_std_int gm_gmp_gmdt_vslprintf(gm_std_uchar *buf, gm_std_uchar *last, const gm_std_char *fmt, gm_std_uchar *dt)
{
	gm_std_uchar				*data;
	gm_std_int					len = 0;





	if (!buf || dt || buf >= last)
	{
		return 0;
	}

	data = dt++;
	switch(*dt)
	{
		//常用基础数据类型(0--63)
	case GMP_GMDT_B:
		{
			
		}
		break;
	case GMP_GMDT_C:
		{
			
		}
		break;
	case GMP_GMDT_UC:
		{
			
		}
		break;
	case GMP_GMDT_S:
		{
			
		}
		break;
	case GMP_GMDT_US:
		{
			
		}
		break;
	case GMP_GMDT_IN:
		{
			
		}
		break;
	case GMP_GMDT_UIN:
		{
			
		}
		break;
	case GMP_GMDT_L:
		{
			
		}
		break;
	case GMP_GMDT_UL:
		{
			
		}
		break;
	case GMP_GMDT_F:
		{
			
		}
		break;
	case GMP_GMDT_UF:
		{
			
		}
		break;
	case GMP_GMDT_D:
		{
			
		}
		break;
	case GMP_GMDT_UD:
		{
			
		}
		break;
	case GMP_GMDT_N:
		{
			
		}
		break;
	case GMP_GMDT_T:
		{
			
		}
		break;
		//容器类型(64--127):
	case GMP_GMDT_A:
		{
			
		}
		break;
	case GMP_GMDT_O:
		{
			
		}
		break;
	case GMP_GMDT_X:
		{
			
		}
		break;
	case GMP_GMDT_JS:
		{
			
		}
		break;
	case GMP_GMDT_IOB:
		{
			
		}
		break;
		//扩展类型(128--255):
	case GMP_GMDT_ST:
		{
			
		}
		break;
	case GMP_GMDT_R:
		{
			
		}
		break;
	default:
		{
			return 0;
		}
	}

	return len;
}









