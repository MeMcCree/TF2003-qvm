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
 *  $Id: sniper.c,v 1.5 2006-11-29 23:19:23 AngelD Exp $
 */
#include "g_local.h"

void    SniperSight_Update(  );

//=========================================================================
// Sniper/Auto Rifle selection function
void TeamFortress_SniperWeapon(  )
{

	self->s.v.impulse = 0;
	if ( self->tfstate & TFSTATE_RELOADING )
		return;
	if ( !( ( self->weapons_carried & WEAP_SNIPER_RIFLE ) && ( self->weapons_carried & WEAP_AUTO_RIFLE ) ) )
		return;
	if ( self->s.v.ammo_shells < 1 )
	{
		G_sprint( self, 2, "not enough ammo.\n" );
		return;
	}
	if ( self->current_weapon == WEAP_SNIPER_RIFLE )
		self->current_weapon = WEAP_AUTO_RIFLE;
	else
		self->current_weapon = WEAP_SNIPER_RIFLE;
	W_SetCurrentAmmo(  );
}

//=========================================================================
// Do the autozoom of the sniper rifle
void TF_zoom( int zoom_level )
{

	if ( self->tfstate & TFSTATE_ZOOMOFF )
		return;
	stuffcmd( self, "fov %d\n", zoom_level );
}

//=========================================================================
// Move the sight to the point the rifle's aiming at
void SniperSight_Update(  )
{
	vec3_t  org, end;
	gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

	if ( !( owner->tfstate & TFSTATE_AIMING ) || owner->current_weapon != WEAP_SNIPER_RIFLE )
	{
		owner->tfstate -= ( owner->tfstate & TFSTATE_AIMING );
		TeamFortress_SetSpeed( owner );
		owner->heat = 0;
		dremove( self );
		return;
	}
	trap_makevectors( owner->s.v.v_angle );
	org[0] = owner->s.v.origin[0] + g_globalvars.v_forward[0] * 10;
	org[1] = owner->s.v.origin[1] + g_globalvars.v_forward[1] * 10;
	org[2] = owner->s.v.absmin[2] + owner->s.v.size[2] * 0.7;

	VectorScale( g_globalvars.v_forward, 9192, end );
	VectorAdd( end, org, end );
	traceline( PASSVEC3( org ), PASSVEC3( end ), 0, self );
	if ( g_globalvars.trace_fraction == 1 )
	{
		setorigin( self, PASSVEC3( owner->s.v.origin ) );
		return;
	}
	vectoangles( g_globalvars.v_forward, self->s.v.angles );
	setorigin( self, PASSVEC3( g_globalvars.trace_endpos ) );
	self->s.v.nextthink = g_globalvars.time + 0.1;
}

//=========================================================================
// Create the sight
void SniperSight_Create(  )
{
	gedict_t *sight;

	if ( self->has_disconnected == 1 )
		return;
	self->tfstate |= TFSTATE_AIMING;
	sight = spawn(  );
	sight->s.v.owner = EDICT_TO_PROG( self );
	sight->s.v.movetype = MOVETYPE_NOCLIP;
	sight->s.v.solid = SOLID_NOT;
	setmodel( sight, "progs/sight.spr" );
	sight->s.v.classname = "timer";
	setorigin( sight, PASSVEC3( self->s.v.origin ) );
	sight->s.v.think = ( func_t ) SniperSight_Update;
	sight->s.v.nextthink = g_globalvars.time + 0.05;
}

// this toggles the snipers autozoom on/off
void TeamFortress_AutoZoomToggle(  )
{
	if ( self->tfstate & TFSTATE_ZOOMOFF )
	{
		self->tfstate = self->tfstate - TFSTATE_ZOOMOFF;
		G_sprint( self, 2, "autozoom ON\n" );
	} else
	{
		self->tfstate = self->tfstate | TFSTATE_ZOOMOFF;
		G_sprint( self, 2, "autozoom OFF\n" );
	}
}


void SniperBulletTouch() {
	vec3_t dir, src;
	float dam_mult;
	float zdif;
	vec3_t f;
	vec3_t g;
	vec3_t h, tmp;
    
    if ( other->s.v.solid == SOLID_TRIGGER )
        return;
    if ( trap_pointcontents( PASSVEC3( self->s.v.origin ) ) == -6 ) {
        dremove( self );
        return;
    }
    if ( other->s.v.takedamage )
    {
	    if (streq(other->s.v.classname, "player")) {
	    	VectorSubtract(self->s.v.origin, src, f);
	    	g[0] = self->s.v.origin[0];
	    	g[1] = self->s.v.origin[1];
	    	g[2] = 0;
	    	h[0] = other->s.v.origin[0];
	    	h[1] = other->s.v.origin[1];
	    	h[2] = 0;
	    	VectorSubtract(g, h, tmp);
	    	VectorNormalize(f);
	    	VectorScale(f, vlen(tmp), f);
	    	VectorAdd(f, self->s.v.origin, f);

	    	zdif = f[2] - other->s.v.origin[2];
	    	tf_data.deathmsg = DMSG_SNIPERRIFLE;
	    	SetVector(other->head_shot_vector, 0, 0, 0);
	    	if (zdif < 0) {
	        	dam_mult = 0.5;
	        	other->leg_damage = other->leg_damage + 2;
	        	TeamFortress_SetSpeed(other);
	        	tf_data.deathmsg = DMSG_SNIPERLEGSHOT;
	        	TF_T_Damage(other, self, PROG_TO_EDICT(self->s.v.owner), self->heat * dam_mult, TF_TD_NOTTEAM, TF_TD_SHOT);
	        	if (other->s.v.health > 0) {
	        		G_sprint(other, 0, "Leg injury!\n");
	        		G_sprint(PROG_TO_EDICT(self->s.v.owner), 1, "Leg shot - that'll slow him down!\n");
	        	}
	        	return;
	      	} else {
	        	if (zdif > 20) {
	          		dam_mult = 2;
	          		stuffcmd(other, "bf\n");
	          		VectorSubtract(other->s.v.origin, self->s.v.origin, other->head_shot_vector);
	          		
	          		tf_data.deathmsg = DMSG_SNIPERHEADSHOT;
	          		TF_T_Damage(other, self, self, self->heat * dam_mult, TF_TD_NOTTEAM, TF_TD_SHOT);
	          		if (other->s.v.health > 0) {
	            		G_sprint(other, 0, "Head injury!\n");
	            		G_sprint(self, 1, "Head shot - that's gotta hurt!\n");
	          		}
	          		return;
	        } else
	          tf_data.deathmsg = DMSG_SNIPERRIFLE;
      		}
  		}
    } else {
        trap_WriteByte( MSG_MULTICAST, SVC_TEMPENTITY );
        if ( streq( self->s.v.classname, "wizspike" ) )
            trap_WriteByte( MSG_MULTICAST, TE_WIZSPIKE );
        else
        {
            if ( streq( self->s.v.classname, "knightspike" ) )
                trap_WriteByte( MSG_MULTICAST, TE_KNIGHTSPIKE );
            else
                trap_WriteByte( MSG_MULTICAST, TE_SPIKE );
        }
        trap_WriteCoord( MSG_MULTICAST, self->s.v.origin[0] );
        trap_WriteCoord( MSG_MULTICAST, self->s.v.origin[1] );
        trap_WriteCoord( MSG_MULTICAST, self->s.v.origin[2] );
        trap_multicast( PASSVEC3( self->s.v.origin ), 2 );
    }
    dremove( self );
}