/*
 *  QWProgs-TF2003
 *  Copyright (C) 2004  [sd] angel
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *  $Id: g_mod_command.c,v 1.4 2005-06-07 04:12:39 AngelD Exp $
 */

#include "g_local.h"
typedef struct {
	char   *command;
	void    ( *Action ) ( int );
} mod_t;
void WP_command( int argc );

const static mod_t   mod_cmds[] = {
	{"wp", WP_command},
	{NULL, NULL}
};



void ModCommand()
{
        char    cmd_command[1024];
        int argc;
        const mod_t  *ucmd;

        argc = trap_CmdArgc();
        if( argc < 2 )
                return;


        trap_CmdArgv( 1, cmd_command, sizeof( cmd_command ) );

	for ( ucmd = mod_cmds; ucmd->command; ucmd++ )
	{
		if ( strcmp( cmd_command, ucmd->command ) )
			continue;
		ucmd->Action( argc );
		return;
	}
	return;

}
extern vec3_t end_pos;

void DrawWPS();
void WP_command( int argc )
{
        char    cmd_command[1024];
        if( argc < 3)
                return;
        
        trap_CmdArgv( 2, cmd_command, sizeof( cmd_command ) );

        if(!strcmp(cmd_command, "add"))
        {
                waypoint_t wp;

                if( argc < 7 )
                        return;

                memset(&wp, 0 ,sizeof(wp));
                trap_CmdArgv( 3, cmd_command, sizeof( cmd_command ) );
                wp.index = atoi( cmd_command );
                trap_CmdArgv( 4, cmd_command, sizeof( cmd_command ) );
                wp.origin[0] = atof( cmd_command );
                trap_CmdArgv( 5, cmd_command, sizeof( cmd_command ) );
                wp.origin[1] = atof( cmd_command );
                trap_CmdArgv( 6, cmd_command, sizeof( cmd_command ) );
                wp.origin[2] = atof( cmd_command );
                wp.teams = 15 ;// (1<<0)+(1<<1)+(1<<2)+(1<<3);
                if( argc > 7 )
                {
                        trap_CmdArgv( 7, cmd_command, sizeof( cmd_command ) );
                        wp.flags = atoi( cmd_command );
                        
                }
                if( argc > 8 )
                {
                        trap_CmdArgv( 8, cmd_command, sizeof( cmd_command ) );
                        wp.teams = atoi( cmd_command );
                }

                if( argc > 9 )
                {
                        trap_CmdArgv( 9, cmd_command, sizeof( cmd_command ) );
                        wp.radius = atof( cmd_command );
                        
                }
                AddWaypoint(&wp);
                return;
        }

        if(!strcmp(cmd_command, "link"))
        {
                wp_link_t link;
                int i1,i2;
                if( argc < 5 )
                        return;

                memset(&link, 0 ,sizeof(link));
                trap_CmdArgv( 3, cmd_command, sizeof( cmd_command ) );
                i1 = atoi( cmd_command );
                trap_CmdArgv( 4, cmd_command, sizeof( cmd_command ) );
                i2 = atoi( cmd_command );
                link.teams = 15;
                if( argc > 5 )
                {
                        trap_CmdArgv( 5, cmd_command, sizeof( cmd_command ) );
                        link.flags = atoi( cmd_command );
                }
                if( argc > 6 )
                {
                        trap_CmdArgv( 6, cmd_command, sizeof( cmd_command ) );
                        link.teams = atoi( cmd_command );
                }

                if( argc > 7 )
                {
                        trap_CmdArgv( 7, cmd_command, sizeof( cmd_command ) );
                        link.req_velocity = atof( cmd_command );
                        
                }
                AddLink( i1, i2, &link);
                return;
        }

        if(!strcmp(cmd_command, "dlink"))
        {
                wp_link_t link;
                int i1,i2;
                if( argc < 5 )
                        return;

                memset(&link, 0 ,sizeof(link));
                trap_CmdArgv( 3, cmd_command, sizeof( cmd_command ) );
                i1 = atoi( cmd_command );
                trap_CmdArgv( 4, cmd_command, sizeof( cmd_command ) );
                i2 = atoi( cmd_command );
                link.teams = 15;
                if( argc > 5 )
                {
                        trap_CmdArgv( 5, cmd_command, sizeof( cmd_command ) );
                        link.flags = atoi( cmd_command );
                }
                if( argc > 6 )
                {
                        trap_CmdArgv( 6, cmd_command, sizeof( cmd_command ) );
                        link.teams = atoi( cmd_command );
                }

                if( argc > 7 )
                {
                        trap_CmdArgv( 7, cmd_command, sizeof( cmd_command ) );
                        link.req_velocity = atof( cmd_command );
                        
                }
                AddLink( i1, i2, &link);
                AddLink( i2, i1, &link);
                return;
        }

        if(!strcmp(cmd_command, "target"))
        {
                if( argc < 6 )
                        return;

                trap_CmdArgv( 3, cmd_command, sizeof( cmd_command ) );
                end_pos[0] = atof( cmd_command );
                trap_CmdArgv( 4, cmd_command, sizeof( cmd_command ) );
                end_pos[1] = atof( cmd_command );
                trap_CmdArgv( 5, cmd_command, sizeof( cmd_command ) );
                end_pos[2] = atof( cmd_command );
                return;
        }
        if(!strcmp(cmd_command, "draw"))
        {
                DrawWPS();
                return;
        }

}
