// =============================================================================
// <integer/convert/decimal/serialize/format/outro.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

outro:

// Write the minimum number of decimal digit characters
ptr -= min;
while (min--) ptr[min] = '0';

// Write the remaining padding characters
uint pc = ' ' | (flags & int_format_pad_zero);
while (pad--) p[pad] = pc;

return size;
