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
 */

#include "g_local.h"

#define MEDKIT_COST 15
#define MEDKIT_HEAL 50
#define MAX_MEDKITS 2

void RemoveMedkit() {
	gedict_t* owner, *te;
	owner = PROG_TO_EDICT(self->s.v.enemy);
	owner->dropped_medkits--;

	SUB_Remove();

	for (te = world; (te = trap_find(te, FOFS(s.v.classname), "medkit"));) {
		if (te->s.v.enemy == EDICT_TO_PROG(owner)) {
			te->heat++;
			if (te->heat > MAX_MEDKITS) te->heat = MAX_MEDKITS;
		}
	}
}

void TouchMedkit() {
	gedict_t* owner, *te;
	float healdmg, used;

	if ( g_globalvars.other == self->s.v.enemy && g_globalvars.time < self->s.v.health + 2 ) return;
	if ( ( other->tfstate & TFSTATE_CANT_MOVE ) || ( other->tfstate & TFSTATE_AIMING ) ) return;
	if ( strneq( other->s.v.classname, "player" ) ) return;
	if ( other->s.v.health <= 0 ) return;

	owner = PROG_TO_EDICT(self->s.v.enemy);
	used = 0;
	if (other->s.v.takedamage) {
    if (streq(other->s.v.classname, "player")) {
      // Concussion heal
      for (te = world; (te = trap_find(te, FOFS(s.v.classname), "timer"));) {
        if (te->s.v.owner != EDICT_TO_PROG(other))
          continue;
        if (te->s.v.think != (func_t)ConcussionGrenadeTimer && te->s.v.think != (func_t)OldConcussionGrenadeTimer)
          continue;
        if (tfset(old_grens)) {
          stuffcmd(other, "v_idlescale 0\nfov 90\n");
          other->eff_info.conc_idle = 0;
        }
        used = 1;
        G_bprint(1, "%s cured %s's concussion\n", owner->s.v.netname, other->s.v.netname);
        if (!TeamFortress_isTeamsAllied(te->team_no, owner->team_no))
          TF_AddFrags(owner, 1);
        dremove(te);
        break;
      }

      // Hallucination heal
      if (other->tfstate & TFSTATE_HALLUCINATING) {
        for (te = world; (te = trap_find(te, FOFS(s.v.classname), "timer"));) {
          if (te->s.v.owner != EDICT_TO_PROG(other))
            continue;
          if (te->s.v.think != (func_t)HallucinationTimer)
            continue;

          used = 1;
          other->tfstate -= (other->tfstate & TFSTATE_HALLUCINATING);
          G_bprint(1, "%s healed %s of his hallucinations\n", owner->s.v.netname, other->s.v.netname);

          ResetGasSkins(other);
          if (tfset_new_gas & GAS_MASK_PALETTE)
            stuffcmd(other, "v_cshift; wait; bf\n");
          if (!TeamFortress_isTeamsAllied(te->team_no, owner->team_no))
            TF_AddFrags(owner, 1);
          dremove(te);
          break;
        }
        if (!te)
          G_conprintf("Warning: Error in Hallucination Timer logic.\n");
      }

      // Tranquilisation heal
      if (other->tfstate & TFSTATE_TRANQUILISED) {
        for (te = world; (te = trap_find(te, FOFS(s.v.classname), "timer"));) {
          if (te->s.v.owner != EDICT_TO_PROG(other))
            continue;
          if (te->s.v.think != (func_t)TranquiliserTimer)
            continue;

          used = 1;
          other->tfstate -= (other->tfstate & TFSTATE_TRANQUILISED);
          TeamFortress_SetSpeed(other);
          G_bprint(1, "%s healed %s's tranquilisation\n", owner->s.v.netname, other->s.v.netname);
          if (!TeamFortress_isTeamsAllied(te->team_no, owner->team_no))
            TF_AddFrags(owner, 1);
          dremove(te);
          break;
        }
        if (!te)
          G_conprintf("Warning: Error in Tranquilisation Timer logic.\n");
      }

      // Blindness heal
      if (other->FlashTime > 0) {
        for (te = world; (te = trap_find(te, FOFS(s.v.netname), "flashtimer"));) {
          if (te->s.v.owner != EDICT_TO_PROG(other))
            continue;
          if (strneq(te->s.v.classname, "timer"))
            continue;

          used = 1;
          other->FlashTime = 0;
          G_bprint(1, "%s cured %s's blindness\n", owner->s.v.netname, other->s.v.netname);
          if (!TeamFortress_isTeamsAllied(te->team_no, owner->team_no))
            TF_AddFrags(owner, 1);
          if (tfset(new_flash))
            disableupdates(other, -1); /* server-side flash */
          break;
        }
        if (!te) {
          G_conprintf("Warning: Error in Flash Timer logic.\n");
          other->FlashTime = 0;
        }
      }

      // Infection heal
      if (other->tfstate & TFSTATE_INFECTED) {
        healdmg = Q_rint(other->s.v.health / 2);
        other->tfstate -= (other->tfstate & TFSTATE_INFECTED);
        tf_data.deathmsg = DMSG_MEDIKIT;
        T_Damage(other, owner, owner, healdmg);
        if (streq(owner->s.v.classname, "player")) {
        	used = 1;
          G_bprint(1, "%s cured %s's infection\n", owner->s.v.netname, other->s.v.netname);
          if (!TeamFortress_isTeamsAllied(other->infection_team_no, owner->team_no))
            TF_AddFrags(owner, 1);
        }
      }

      // Put out flames
      if (other->numflames > 0) {
      	used = 1;
        sound(other, 1, "items/r_item1.wav", 1, 1);
        other->numflames = 0;
        if (streq(owner->s.v.classname, "player")) {
          G_bprint(1, "%s put out %s's fire.\n", owner->s.v.netname, other->s.v.netname);
        }
      }

      if (other->s.v.health < other->s.v.max_health) {
      	used = 1;
        T_Heal(other, MEDKIT_HEAL, 0);
      }
    }
  }

  if (used) {
		sound(other, 3, "items/r_item1.wav", 1, 1);
		RemoveMedkit();
	}
}

void ThrowMedkit() {
	gedict_t* newmis, *te, *tt;
	vec3_t  vtemp;

	if (self->ammo_medikit < MEDKIT_COST) return;

	self->ammo_medikit -= MEDKIT_COST;
	self->dropped_medkits++;

	sound( self, CHAN_ITEM, "weapons/lock4.wav", 1, 1 );

	newmis = spawn();
	newmis->s.v.enemy = EDICT_TO_PROG(self);
	newmis->s.v.health = g_globalvars.time;
	newmis->heat = MAX_MEDKITS + 1;
	newmis->s.v.movetype = MOVETYPE_TOSS;
	newmis->s.v.solid = SOLID_TRIGGER;
	newmis->s.v.classname = "medkit";
	newmis->team_no = self->team_no;
	trap_makevectors(self->s.v.v_angle);
	if (self->s.v.v_angle[0]) {
		VectorScale(g_globalvars.v_forward, 400, newmis->s.v.velocity);
		VectorScale(g_globalvars.v_up, 200, vtemp);
		VectorAdd(vtemp, newmis->s.v.velocity, newmis->s.v.velocity );
	} else {
		aim(newmis->s.v.velocity);
		VectorScale(newmis->s.v.velocity, 400, newmis->s.v.velocity);
		newmis->s.v.velocity[2] = 200;
	}

	setsize( newmis, 0, 0, 0, 32, 32, 56 );
	setorigin( newmis, PASSVEC3( self->s.v.origin ) );
	newmis->s.v.nextthink = g_globalvars.time + 60;
	newmis->s.v.think = (func_t)RemoveMedkit;
	newmis->s.v.touch = (func_t)TouchMedkit;

	setmodel(newmis, "maps/b_bh25.bsp");

	for (te = world; (te = trap_find(te, FOFS(s.v.classname), "medkit"));) {
		if (te->s.v.enemy == EDICT_TO_PROG(self)) {
			te->heat--;
			if (te->heat == 0) {
				self->dropped_medkits--;
				dremove(te);
			}
		}
	}
}