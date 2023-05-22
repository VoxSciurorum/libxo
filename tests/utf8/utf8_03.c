/*
 * Copyright (c) 2023, Juniper Networks, Inc.
 * All rights reserved.
 * This SOFTWARE is licensed under the LICENSE provided in the
 * ../Copyright file. By downloading, installing, copying, or otherwise
 * using the SOFTWARE, you agree to be bound by the terms of that
 * LICENSE.
 * Phil Shafer, May 2023
 */

/*
 * This is generated by the code in the "unicode" branch, based on the file
 * UnicodeData.txt from unicode.org:
 *   https://unicode.org/Public/UNIDATA/UnicodeData.txt
 * I've attempted to make it simple, but can't stop it from being ugly.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wctype.h>

#include "xo.h"
#include "xo_encoder.h"
#include "xo_utf8.h"

void
test_xo_utf8_wtolower (void)
{
    wchar_t wc;
    for (wchar_t i = 1; i < 0x1f000; i++) {
	wc = xo_utf8_wtolower(i);
	if (i != wc) {
	    xo_emit("{:base/%#06x} {:lower/%#06x}\n", i, wc);
	}
    }
}

void
test_xo_utf8_wtoupper (void)
{
    wchar_t wc;
    for (wchar_t i = 1; i < 0x1f000; i++) {
	wc = xo_utf8_wtoupper(i);
	if (i != wc) {
	    xo_emit("{:base/%#06x} {:lower/%#06x}\n", i, wc);
	}
    }
}

int
main (int argc, char **argv)
{
    int lower = 1;
    int upper = 1;
    int raw = 0;
    char *file = NULL;

    argc = xo_parse_args(argc, argv);
    if (argc < 0)
	return 1;

    for (argc = 1; argv[argc]; argc++) {
	if (xo_streq(argv[argc], "lower"))
	    upper = 0;
	else if (xo_streq(argv[argc], "upper"))
	    lower = 0;

    }

    xo_open_container("top");

    if (lower)
	test_xo_utf8_wtolower();

    if (upper)
	test_xo_utf8_wtoupper();

    xo_finish();

    return 0;
}
