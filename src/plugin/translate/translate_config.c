#include <locale.h>
#include <langinfo.h>
#include <string.h>
#include "dosemu_debug.h"
#include "translate.h"
#include "dosemu_charset.h"
#include "dosemu_config.h"
#include "init.h"
#include "emu.h"
#include "video.h"
#include "utilities.h"

struct translate_config_t trconfig; /* Intialized to nulls */

static void config_translate_scrub(void)
{
    k_printf("config.term_charset=%d\n", config.term_charset);
    /* set the character sets used base upon config.term_charset */
    if (!trconfig.paste_charset)
	trconfig.paste_charset = lookup_charset("default");
    if (!trconfig.keyb_charset)
	trconfig.keyb_charset = trconfig.paste_charset;
    switch (config.term_charset) {
    case CHARSET_LATIN1:
    case CHARSET_LATIN2:
    case CHARSET_LATIN:
    case CHARSET_KOI8:
    case CHARSET_FULLIBM:
    case CHARSET_IBM:
	error("WARNING: $_term_char_set is obsolete. "
              "Use $_external_char_set and $_internal_char_set instead.\n");
    default:
	if (!trconfig.video_mem_charset) 
		trconfig.video_mem_charset = lookup_charset("cp437");
	if (!trconfig.keyb_config_charset)
		trconfig.keyb_config_charset = 
			get_terminal_charset(lookup_charset("cp437"));
	if (!trconfig.output_charset)
		trconfig.output_charset = lookup_charset("default");
	if (!trconfig.dos_charset)
		trconfig.dos_charset = lookup_charset("cp437");
	break;
    }
    v_printf("video_mem_charset=%s\n", 
	    trconfig.video_mem_charset?(trconfig.video_mem_charset->names)[0]:"<NULL>");
    k_printf("keyb_config_charset=%s\n", 
	    trconfig.keyb_charset?trconfig.keyb_config_charset->names[0]:"<NULL>");
    v_printf("output_charset=%s\n", 
	    trconfig.output_charset?trconfig.output_charset->names[0]:"<NULL>");
    k_printf("paste_charset=%s\n", 
	    trconfig.paste_charset?trconfig.paste_charset->names[0]:"<NULL>");
    k_printf("keyb_charset=%s\n", 
	    trconfig.keyb_charset?trconfig.keyb_charset->names[0]:"<NULL>");
    d_printf("dos_charset=%s\n", 
	    trconfig.dos_charset?trconfig.dos_charset->names[0]:"<NULL>");
}

CONSTRUCTOR(static void init(void))
{
	register_config_scrub(config_translate_scrub);
}
