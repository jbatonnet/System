/*
 * gmisc.c: Misc functions with no place to go (right now)
 *
 * Author:
 *   Aaron Bockover (abockover@novell.com)
 *
 * (C) 2006 Novell, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include "glib.h"

#include <windows.h>
#include <direct.h>
#include <io.h>

const gchar *
g_getenv(const gchar *variable)
{
	gunichar2 *var, *buffer;
	gchar* val = NULL;
	gint32 buffer_size = 1024;
	gint32 retval;
	var = u8to16(variable); 
	buffer = g_malloc(buffer_size*sizeof(gunichar2));
	retval = GetEnvironmentVariableW (var, buffer, buffer_size);
	if (retval != 0) {
		if (retval > buffer_size) {
			g_free (buffer);
			buffer_size = retval;
			buffer = g_malloc(buffer_size*sizeof(gunichar2));
			retval = GetEnvironmentVariableW (var, buffer, buffer_size);
		}
		val = u16to8 (buffer);
	} else {
		if (GetLastError () != ERROR_ENVVAR_NOT_FOUND){
			val = g_malloc (1);
			*val = 0;
		}
	}
	g_free(var);
	g_free(buffer);
	return val; 
}

gboolean
g_setenv(const gchar *variable, const gchar *value, gboolean overwrite)
{
	gunichar2 *var, *val;
	gboolean result;
	var = u8to16(variable); 
	val = u8to16(value);
	result = (SetEnvironmentVariableW(var, val) != 0) ? TRUE : FALSE;
	g_free(var);
	g_free(val);
	return result;
}

void
g_unsetenv(const gchar *variable)
{
	gunichar2 *var;
	var = u8to16(variable); 
	SetEnvironmentVariableW(var, L"");
	g_free(var);
}

gchar*
g_win32_getlocale(void)
{
	LCID lcid = GetThreadLocale();
	gchar buf[19];
	gint ccBuf = GetLocaleInfo(lcid, LOCALE_SISO639LANGNAME, buf, 9);
	buf[ccBuf - 1] = '-';
	ccBuf += GetLocaleInfo(lcid, LOCALE_SISO3166CTRYNAME, buf + ccBuf, 9);
	return strdup(buf);
}

gboolean
g_path_is_absolute (const char *filename)
{
	g_return_val_if_fail (filename != NULL, FALSE);

	if (filename[0] != '\0' && filename[1] != '\0') {
		if (filename[1] == ':' && filename[2] != '\0' &&
			(filename[2] == '\\' || filename[2] == '/'))
			return TRUE;
		/* UNC paths */
		else if (filename[0] == '\\' && filename[1] == '\\' && 
			filename[2] != '\0')
			return TRUE;
	}

	return FALSE;
}

const gchar *
g_get_home_dir (void)
{
	/* FIXME */
	const gchar *drive = g_getenv ("HOMEDRIVE");
	const gchar *path = g_getenv ("HOMEPATH");
	gchar *home_dir = NULL;
	
	if (drive && path) {
		home_dir = g_malloc(strlen(drive) + strlen(path) +1);
		if (home_dir) {
			sprintf(home_dir, "%s%s", drive, path);
		}
	}

	return home_dir;
}

const char *
g_get_user_name (void)
{
	const char * retName = g_getenv ("USER");
	if (!retName)
		retName = g_getenv ("USERNAME");
	return retName;
}

static const char *tmp_dir;

const gchar *
g_get_tmp_dir (void)
{
	if (tmp_dir == NULL){
		if (tmp_dir == NULL){
			tmp_dir = g_getenv ("TMPDIR");
			if (tmp_dir == NULL){
				tmp_dir = g_getenv ("TMP");
				if (tmp_dir == NULL){
					tmp_dir = g_getenv ("TEMP");
					if (tmp_dir == NULL)
						tmp_dir = "C:\\temp";
				}
			}
		}
	}
	return tmp_dir;
}

