/******************************************************************
 * Copyright (C) 2003 - 2005 by SG Software.
 *
 * SG MPFC. Interface for plugins manager functions.
 * $Id$
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either version 2 
 * of the License, or (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public 
 * License along with this program; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, 
 * MA 02111-1307, USA.
 */

#ifndef __SG_MPFC_PMNG_H__
#define __SG_MPFC_PMNG_H__

#include "types.h"
#include "cfg.h"
#include "csp.h"
#include "ep.h"
#include "inp.h"
#include "logger.h"
#include "outp.h"
#include "plugin.h"
#include "vfs.h"
#include "wnd.h"

/* Plugin manager type */
typedef struct tag_pmng_t
{
	/* Plugin list */
	int m_num_plugins;
	plugin_t **m_plugins;

	/* Current output plugin */
	out_plugin_t *m_cur_out;

	/* Configuration variables list */
	cfg_node_t *m_cfg_list;

	/* Root window */
	wnd_t *m_root_wnd;

	/* Logger object */
	logger_t *m_log;

	/* Player window */
	wnd_t *m_player_wnd;
} pmng_t;

/* Initialize plugins */
pmng_t *pmng_init( cfg_node_t *list, logger_t *log, wnd_t *wnd_root );

/* Unitialize plugins */
void pmng_free( pmng_t *pmng );

/* Load plugins */
bool_t pmng_load_plugins( pmng_t *pmng );

/* Add a plugin */
void pmng_add_plugin( pmng_t *pmng, plugin_t *p );

/* Send command message to player */
void pmng_player_command( pmng_t *pmng, char *cmd, char *params_fmt, ... );

/* Autostart general plugins */
void pmng_autostart_general( pmng_t *pmng );

/* Search for input plugin supporting given format */
in_plugin_t *pmng_search_format( pmng_t *pmng, char *filename, char *ext );

/* Search for input plugin supporting given content-type */
in_plugin_t *pmng_search_content_type( pmng_t *pmng, char *content );

/* Apply effect plugins */
int pmng_apply_effects( pmng_t *pmng, byte *data, int len, int fmt, 
		int freq, int channels );

/* Search for plugin with a specified name */
plugin_t *pmng_search_by_name( pmng_t *pmng, char *name, 
		plugin_type_t type_mask );

/* Plugin glob handler */
void pmng_glob_handler( struct tag_vfs_file_t *file, void *data );

/* Check if specified plugin is already loaded */
bool_t pmng_is_loaded( pmng_t *pmng, char *name, plugin_type_t type_mask );

/* Find charset plugin which supports specified set */
cs_plugin_t *pmng_find_charset( pmng_t *pmng, char *name, int *index );

/* Get configuration variables list */
cfg_node_t *pmng_get_cfg( pmng_t *pmng );

/* Get logger */
logger_t *pmng_get_logger( pmng_t *pmng );

/* Create a plugin name */
char *pmng_create_plugin_name( char *filename );

/* Stop all general plugins */
void pmng_stop_general_plugins( pmng_t *pmng );

/*
 * Plugins iteration functions
 */

/* Iterator type */
typedef struct
{
	/* Plugin manager object */
	pmng_t *m_pmng;

	/* Plugin types we are looking for */
	plugin_type_t m_type_mask;

	/* Current plugin index */
	int m_index;
} pmng_iterator_t;

/* Start iteration */
pmng_iterator_t pmng_start_iteration( pmng_t *pmng, plugin_type_t type_mask );

/* Make an iteration */
plugin_t *pmng_iterate( pmng_iterator_t *iter );

/* Check if effect is enabled */
bool_t pmng_is_effect_enabled( pmng_t *pmng, plugin_t *ep );

/* Enable/disable effect */
void pmng_enable_effect( pmng_t *pmng, plugin_t *ep, bool_t enable );

#endif

/* End of 'pmng.h' file */

