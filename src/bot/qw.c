/*
 *  QWProgs-TF2003
 *  Copyright (C) 2004  [sd] angel
 *
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
 *  $Id: qw.c,v 1.2 2005-05-05 14:51:44 AngelD Exp $
 */
#include "g_local.h"

int CL_KeyState( int key )
{
	return ( self->keys & key ) != 0;
}

void Bot_CL_KeyMove(  )
{
	int     forwardmove = 0, sidemove = 0, upmove = 0;
	int     buttons = 0;

	buttons = ( ( self->s.v.button0 ) ? 1 : 0 ) + ( ( self->s.v.button2 ) ? 2 : 0 );

	sidemove += self->maxstrafespeed * CL_KeyState( KEY_MOVERIGHT );
	sidemove -= self->maxstrafespeed * CL_KeyState( KEY_MOVELEFT );

	upmove += 200 * CL_KeyState( KEY_MOVEUP );
	upmove -= 200 * CL_KeyState( KEY_MOVEDOWN );

	forwardmove += self->maxfbspeed * CL_KeyState( KEY_MOVEFORWARD );
	forwardmove -= self->maxfbspeed * CL_KeyState( KEY_MOVEBACK );

	if ( self->s.v.v_angle[0] > 80 )
		self->s.v.v_angle[0] = 80;
	else
	{
		if ( self->s.v.v_angle[0] < -70 )
			self->s.v.v_angle[0] = -70;
	}
/*	if (self->current_weapon == WEAP_ASSAULT_CANNON && self->s.v.button0) 
	{
                sidemove = 0;
                forwardmove = 0;
                upmove = 0;
                return;
        }*/

	self->s.v.v_angle[2] = 0;
	self->s.v.v_angle[1] = anglemod( self->s.v.v_angle[1] );
//	VectorCopy(self->s.v.v_angle,self->s.v.angles); 

	trap_SetBotCMD( NUM_FOR_EDICT( self ), g_globalvars.frametime * 1000,
//                      self->s.v.angles[0], self->s.v.angles[1], self->s.v.angles[2],
			self->s.v.v_angle[0], self->s.v.v_angle[1], self->s.v.v_angle[2],
			forwardmove, sidemove, upmove, buttons, self->s.v.impulse );
}
void BotFrame( void )
{
	gedict_t *te, *oself;

	oself = self;
	for ( te = world; ( te = trap_find( te, FOFS( s.v.classname ), "player" ) ); )
	{
		if ( te->has_disconnected )
			continue;

		if ( !te->isBot )
			continue;

		self = te;
		if( !tf_data.enable_bot )
		{
		        botDisconnect( self );
		        continue;
		}
		{
        		self->s.v.button0 = 0;
        		self->s.v.button2 = 0;
        		self->s.v.impulse = 0;
        		Bot_AI(  );
		}
		Bot_CL_KeyMove(  );
	}
	self = oself;

}

void botConnect( int whichteam, int whichClass )
{
	gedict_t *oself;
	int     ednum;

	gedict_t *ent = &g_edicts[ednum = trap_AddBot( PickAName(  ), 0, 0, "base" )];

	if ( ent == world )
	{
		G_sprint( self, 2, "cannot add bot\n" );
		return;
	}

	oself = self;
	self = ent;
	self->has_disconnected = 0;
	self->bot_skin = whichClass;
	self->bot_team = whichteam;
	PutClientInServer(  );
	TeamFortress_TeamSet( whichteam );
	self->s.v.impulse = whichClass + TF_CHANGEPC;
	TeamFortress_ChangeClass(  );
	
	ClearAllWaypoints(  );
	ClearAllTargets(  );
	self->action = BOT_RESUPPLYING;
	self->obs_time = 0;
	self->oldAction = BOT_IDLE;
//	SetVector( self->pipeLocation, 0, 0, 0 );

	self = oself;

}

void botDisconnect( gedict_t * te )
{
	gedict_t *oself;

	if ( !te->isBot )
	{
		G_bprint( 2, "WARNING!!! Trying to disconnect non bot client\n" );
		return;
	}
	oself = self;
	self = te;
	ClientDisconnect(  );
	trap_RemoveBot( NUM_FOR_EDICT( te ) );
	self = oself;
}
