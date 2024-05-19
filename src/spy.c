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
 *  $Id: spy.c,v 1.18 2006-11-29 23:19:23 AngelD Exp $
 */
#include "g_local.h"

/*
   ========================================================
   Functions for the SPY class and associated weaponry                          
   ========================================================
   */

void    TeamFortress_SpyCalcName( gedict_t * spy );
void    TeamFortress_SpyUndercoverThink(  );
void    GasGrenadeMakeGas(  );
void    T_TranqDartTouch(  );
void    spawn_touchblood( float damage );

//=========================================================================
// Function handling the Spy's feign death ability
void TeamFortress_PlayerLostFlag(void);
void PlayerSetDieFrames(int isdead);
void _spy_up(  )
{
    self->s.v.nextthink += 0.1;
    self->s.v.think = (func_t)_spy_up;
    self->s.v.frame -= 1;
    if( self->s.v.frame <= self->frame_info.end ){
        self->s.v.think = (func_t) player_stand1;
    }
}

void SpyFeignDeathNotes( gedict_t * targ, gedict_t * attacker )
{
    float   rnum;
    char   *deathstring = "";

    rnum = g_random();
    if ( tf_data.cb_prematch_time + 3 > g_globalvars.time )
        return;
    if ( strneq( targ->s.v.classname, "player" ) )
    {
        if ( streq( targ->s.v.classname, "building_sentrygun" ) )
        {
            if ( streq( attacker->s.v.classname, "teledeath" ) )
            {
                G_bprint( 1, "%s's sentrygun was telefragged by %s\n", targ->real_owner->s.v.netname,
                        PROG_TO_EDICT( attacker->s.v.owner )->s.v.netname );
                return;
            }
            if ( streq( attacker->s.v.classname, "player" ) )
            {
                if ( attacker == targ->real_owner )
                {
                    G_bprint( 1, "%s destroys his sentrygun\n", targ->real_owner->s.v.netname );
                    return;
                }
                G_bprint( 1, "%s's sentrygun was destroyed by %s\n", targ->real_owner->s.v.netname,
                        attacker->s.v.netname );
                return;
            }
        }
    }
    if ( strneq( targ->s.v.classname, "player" ) )
        return;

    if ( streq( attacker->s.v.classname, "teledeath" ) )
    {
        G_bprint( 1, "%s was telefragged by %s\n", targ->s.v.netname,
                PROG_TO_EDICT( attacker->s.v.owner )->s.v.netname );
        return;
    }
    if ( streq( attacker->s.v.classname, "teledeath2" ) )
    {
        G_bprint( 1, "Satan's power deflects %s's telefrag\n", targ->s.v.netname );
        logfrag( targ, targ );
        return;
    }
    if ( tf_data.deathmsg == DMSG_TEAMKILL )
    {
        G_bprint( 1, "%s shoots his teammate one too many times.\n", targ->s.v.netname );
        return;
    }
    if ( streq( attacker->s.v.classname, "info_tfgoal" ) || streq( attacker->s.v.classname, "item_tfgoal" ) )
    {
        if ( attacker->deathtype && attacker->deathtype[0] )
        {
            G_bprint( 1, "%s%s", targ->s.v.netname, attacker->deathtype );
        }
        logfrag( targ, targ );
        return;
    }
    //player vs player or bot
    if ( streq( attacker->s.v.classname, "player" ) || streq( attacker->s.v.classname, "bot" ) )
    {
        if ( targ == attacker )
        {
            if ( tfset(birthday) && g_random() < 0.3 )
            {
                if ( g_random() < 0.1 )
                {
                    G_bprint( 1, "It's %s's party and he'll cry if he wants to!\n",
                            targ->s.v.netname );
                    return;
                }
                if ( g_random() < 0.5 )
                    G_bprint( 1, "%s gets too selfish with his gifts\n", targ->s.v.netname );
                else
                    G_bprint( 1, "%s wasn't born so beautiful after all\n", targ->s.v.netname );
                return;
            }
            switch ( tf_data.deathmsg )
            {
                case DMSG_GREN_HAND:
                    switch ( targ->playerclass )
                    {
                        case PC_SNIPER:
                            deathstring = "%s got splattered by his own grenade\n";
                            break;
                        case PC_SOLDIER:
                            deathstring = "%s sat on his own grenade\n";
                            break;
                        case PC_DEMOMAN:
                            deathstring = "%s got to know his grenade too well\n";
                            break;
                        case PC_MEDIC:
                            deathstring = "%s caught the end of his own grenade\n";
                            break;
                        case PC_HVYWEAP:
                            deathstring = "%s got too close to his own grenade\n";
                            break;
                        case PC_PYRO:
                            deathstring = "%s let his own grenade get the best of him\n";
                            break;
                        case PC_SPY:
                            deathstring = "%s tiptoed over his own grenade\n";
                            break;
                        case PC_ENGINEER:
                            deathstring = "%s stared at his grenade too long\n";
                            break;
                        default:
                            deathstring = "%s grenades himself\n";
                            break;
                    }
                    break;
                case DMSG_GREN_NAIL:
                    deathstring = "%s hammers himself\n";
                    break; 
                case DMSG_GREN_MIRV:
                    switch ( targ->playerclass )
                    {
                        case PC_DEMOMAN:
                            deathstring = "%s practiced his own Mirv dance\n";
                            break;
                        case PC_HVYWEAP:
                            deathstring = "%s allowed his Mirv to turn against him\n";
                            break;
                        default:
                            deathstring = "%s goes to pieces\n";
                            break;

                    }
                    break;
                case DMSG_GREN_PIPE:
                    deathstring = "%s ambushes himself with his own pipebombs\n";
                    break;
                case DMSG_PIPEBOMB:
                    deathstring = "%s tried to juggle his own pipebombs\n";
                    break;
                case DMSG_GREN_GAS:
                    deathstring = "%s chokes on his own gas\n";
                    break;
                case DMSG_GREN_EMP:
                    deathstring = "%s explodes his ammo and body\n";
                    break;
                case DMSG_CALTROP:
                    deathstring = "%s stepped on too many of his own caltrops\n";
                    break;
                case DMSG_GREN_FLASH:
                    deathstring = "%s is charred by his own flash grenade\n";
                    break;
                case DMSG_GREN_EMP_AMMO:
                    deathstring = "%s detonates an ammo box too close to him\n";
                    break;
                case DMSG_DETPACK:
                    deathstring = "%s set the detpack and forgot to run\n";
                    break;
                case DMSG_BIOWEAPON:
                    deathstring = "%s died impossibly!\n";
                    break;
                case DMSG_ROCKETL:
                    if ( rnum < 0.5 )
                        deathstring = "%s becomes bored with life\n";
                    else
                        deathstring = "%s checks if his weapon is loaded\n";
                    break;
                case DMSG_INCENDIARY:
                    deathstring = "%s chars himself with an incendiary rocket\n";
                    break;
                case DMSG_GRENADEL:
                    deathstring = "%s tries to put the pin back in\n";
                    break;
                case DMSG_FLAME:
                    deathstring = "%s torches himself\n";
                    break;
                case DMSG_LIGHTNING:
                    if ( targ->s.v.waterlevel > 1 )
                        deathstring = "%s discharges into the water.\n";
                    break;
                case DMSG_SG_EXPLODION:
                    deathstring = "%s gets too friendly with his sentrygun.\n";
                    break;
                case DMSG_DISP_EXPLODION:
                    deathstring = "%s dispenses with himself.\n";
                    break;
            }
            G_bprint( 1, deathstring, targ->s.v.netname );
            return;
        }       //end of sucides
        else
        {
            if ( teamplay && attacker->team_no == targ->team_no && attacker->team_no > 0 )
            {
                if ( tfset(birthday) && g_random() < 0.3 )
                {
                    if ( g_random() < 0.3 )
                        G_bprint( 1, "%s is a party-pooper!\n", targ->s.v.netname );
                    else
                        G_bprint( 1, "%s gives gifts to his teammates!\n", targ->s.v.netname );
                    return;
                }
                switch ( ( int ) ( g_random() * 4 ) )
                {
                    case 0:
                        deathstring = "%s mows down teammate %s\n";
                        break;
                    case 1:
                        deathstring = "%s checks his glasses after killing %s\n";
                        break;
                    case 2:
                        deathstring = "%s gets a frag for the other team with %s's death\n";
                        break;
                    default:
                        deathstring = "%s killed his supposed friend %s\n";
                        break;
                }
                if ( tf_data.deathmsg == DMSG_MEDIKIT )
                {
                    G_bprint( 1, "%s didn't survive the operation by %s\n", targ->s.v.netname,
                            attacker->s.v.netname );
                    return;
                }
                G_bprint( 1, deathstring, attacker->s.v.netname, targ->s.v.netname );
                return;
            }   //end of teamkills
            else
            {
                logfrag( attacker, targ );
                if ( tfset(birthday) && g_random() < 0.5 )
                {
                    switch ( tf_data.deathmsg )
                    {
                        case 9:
                            deathstring = "%s chews on %s's nails!\n";
                            break;
                        case 10:
                            deathstring = "%s gathers the darling buds of %s's Mirv grenade\n";
                            break;
                        case 30:
                            deathstring = "%s's presents go up in %s's EMP presence.\n";
                            break;
                        case 35:
                            G_bprint( 1, "%s goes POP!\n", targ->s.v.netname );
                            return;
                        case 31:
                            deathstring = "%s stands to near %s's birthday surprise\n";
                            break;
                        case 12:
                            deathstring = "%s eats %s's good cheer!\n";
                            if ( g_random() < 0.1 )
                                G_bprint( 1, "Damn that jokey smurf!\n" );
                            break;
                        case 16:
                            deathstring = "%s cut the red ribbon of %s's detpack\n";
                            break;
                        case 5:
                            deathstring = "%s recieves a gift from %s\n";
                            if ( targ->s.v.health < -40 )
                                deathstring = "%s plays pass-the-parcel with %s\n";
                            break;
                        case 6:
                            deathstring = "%s rides %s's firecracker\n";
                            if ( targ->s.v.health < -40 )
                            {
                                G_bprint( 1,
                                        "%s gets turned into little %s's by %s's firecracker",
                                        targ->s.v.netname, targ->s.v.netname,
                                        attacker->s.v.netname );
                                return;
                            }
                            break;
                        case 15:
                            if ( ( int ) ( g_random() * 2 ) )
                                deathstring = "%s gets too close to %s's kitchen\n";
                            else
                                deathstring = "%s plays with %s's fire\n";
                            break;
                        case 18:
                            if ( ( int ) ( g_random() * 3 ) )
                                deathstring = "%s blocks %s's birthday bullet with his chest\n";
                            else
                                deathstring = "%s gets party popped by %s\n";
                            break;
                        case 29:
                            if ( ( int ) ( g_random() * 2 ) )
                                deathstring =
                                    "%s ALMOST catches %s's bullet between his teeth!\n";
                            else
                                deathstring = "%s loves snipers like %s\n";
                            break;
                        case 28:
                            deathstring = "%s won't run crying to %s anymore\n";
                            break;
                        case 19:
                            deathstring = "%s collects %s's highspeed gifts.\n";
                            break;
                        case 20:
                            deathstring = "%s died. I blame %s\n";
                            break;
                        case 22:
                            deathstring = "%s gets a gift in the back from %s\n";
                            break;
                        case 2:
                            deathstring = "%s gets a double of %s's buck\n";
                            break;
                        case 25:
                            deathstring = "%s is all partied out by %s\n";
                            break;
                        case 26:
                            deathstring = "%s gets derailed by %s\n";
                            break;
                        case 3:
                            deathstring = "%s gets no say in it, no say in it at all! sings %s\n";
                            break;
                        case 33:
                            deathstring = "%s gets all fired up by %s\n";
                            break;
                        default:    //death msg 8??? 
                            if ( ( int ) ( g_random() * 2 ) )
                                deathstring = "%s recieves a gift from %s\n";
                            else
                                deathstring = "%s has a happy birthday, thanks to %s\n";
                            break;

                    }
                    G_bprint( 1, deathstring, targ->s.v.netname, attacker->s.v.netname );
                    return;
                }   //end of player vs player Birthday messages
                //normal player vs player messages
                switch ( tf_data.deathmsg )
                {
                    case DMSG_GREN_HAND:
                        switch ( attacker->playerclass )
                        {
                            case PC_SNIPER:
                                deathstring = "%s got up-close and personal with %s's grenade\n";
                                break;
                            case PC_SOLDIER:
                                deathstring = "%s played catch with %s's grenade\n";
                                break;
                            case PC_DEMOMAN:
                                deathstring = "%s received a pineapple enema from %s\n";
                                break;
                            case PC_MEDIC:
                                deathstring = "%s fetched %s's pineapple\n";
                                break;
                            case PC_HVYWEAP:
                                deathstring = "%s caught too much shrapnel from %s's grenade\n";
                                break;
                            case PC_PYRO:
                                deathstring = "%s tried to pick up %s's hot potato\n";
                                break;
                            case PC_SPY:
                                deathstring = "%s thought %s was tossing him a spare grenade\n";
                                break;
                            case PC_ENGINEER:
                                deathstring =
                                    "%s stops to ponder the technical details of %s's grenade\n";
                                break;
                            default:
                                deathstring = "%s surfs on a grenade from %s\n";
                                break;
                        }
                        break;
                    case DMSG_GREN_NAIL:
                        deathstring = "%s gets flayed by %s's nail grenade\n";
                        break;
                    case DMSG_GREN_MIRV:
                        if ( attacker->playerclass == 4 )
                            deathstring = "%s does a dance on %s's Mirv grenade\n";
                        else
                            deathstring = "%s gets spammed by %s's Mirv grenade\n";
                        break;
                    case DMSG_GREN_PIPE:
                        deathstring = "%s is caught by %s's pipebomb trap\n";
                        break;
                    case DMSG_PIPEBOMB:
                        deathstring = "%s fell victim to %s's fireworks\n";
                        break;
                    case DMSG_GREN_GAS:
                        deathstring = "%s gags on %s's noxious gasses\n";
                        break;
                    case DMSG_GREN_EMP:
                        deathstring = "%s's ammo detonates him as %s's EMP fries it\n";
                        break;
                    case DMSG_CALTROP:
                        deathstring = "%s stepped on too many of %s's caltrops\n";
                        break;
                    case DMSG_GREN_FLASH:
                        deathstring = "%s is charred by %s's flash grenade\n";
                        break;
                    case DMSG_GREN_EMP_AMMO:
                        deathstring = "%s stands near some ammo as %s's EMP nukes it\n";
                        break;
                    case DMSG_DETPACK:
                        deathstring = "%s reaches orbit via %s's detpack\n";
                        break;
                    case DMSG_DETPACK_DIS:
                        deathstring = "%s cut the red wire of %s's detpack\n";
                        break;
                    case DMSG_BIOWEAPON:
                        deathstring = "%s dies from %s's mysterious tropical disease\n";
                        break;
                    case DMSG_BIOWEAPON_ATT:
                        deathstring = "%s escapes infection from %s by dying first\n";
                        break;
                    case DMSG_GRENADEL:
                        deathstring = "%s eats %s's pineapple\n";
                        if ( targ->s.v.health < -40 )
                            deathstring = "%s was gibbed by %s's grenade\n";
                        break;
                    case DMSG_ROCKETL:
                        deathstring = "%s rides %s's rocket\n";
                        if ( targ->s.v.health < -40 )
                            deathstring = "%s was gibbed by %s's rocket\n";
                        break;
                    case DMSG_FLAME:
                        switch ( ( int ) ( rnum * 5 ) )
                        {
                            case 0:
                                deathstring = "%s is burnt up by %s's flame\n";
                                break;
                            case 1:
                                deathstring = "%s is fried by %s's fire\n";
                                break;
                            case 2:
                                deathstring = "%s feels %s's fire of wrath\n";
                                break;
                            case 3:
                                deathstring = "%s is reduced to ashes by %s\n";
                                break;
                            default:
                                deathstring = "%s is grilled by %s's flame\n";
                                break;
                        }
                        break;
                    case DMSG_AXE:
                        switch ( attacker->playerclass )
                        {
                            case PC_SPY:
                                deathstring = "%s was knife-murdered by %s\n";
                                break;
                            case PC_SCOUT:
                                deathstring = "%s's mellon was split by %s\n";
                                break;
                            case PC_SNIPER:
                                deathstring = "%s was put on the chop block by %s\n";
                                break;
                            case PC_SOLDIER:
                                deathstring = "%s was sliced and diced by %s's blade\n";
                                break;
                            case PC_DEMOMAN:
                                deathstring = "%s is split from crotch to sternum by %s's axe swing\n";
                                break;
                            case PC_HVYWEAP:
                                deathstring = "%s is split in two with a powerful axe blow from %s\n";
                                break;
                            case PC_PYRO:
                                deathstring = "%s's death put another notch on %s's axe\n";
                                break;
                            default:
                                deathstring = "%s's death put another notch on %s's axe\n";
                                break;
                        }
                        break;

                    case DMSG_SPANNER:
                        deathstring = "%s was spanner-murdered by %s\n";
                        break;
                    case DMSG_SHOTGUN:
                        switch ( attacker->playerclass )
                        {
                            case PC_SCOUT:
                                deathstring = "%s got too close to %s's muzzleflash\n";
                                break;
                            case PC_SOLDIER:
                                deathstring = "%s practices being %s's clay pigeon\n";
                                break;
                            case PC_DEMOMAN:
                                deathstring = "%s was on the receiving end of %s's shotgun barrel\n";
                                break;
                            case PC_MEDIC:
                                deathstring = "%s was fed a lead diet by %s\n";
                                break;
                            case PC_HVYWEAP:
                                deathstring = "%s got blasted by %s's last resort\n";
                                break;
                            case PC_PYRO:
                                deathstring = "%s got more than a powderburn from %s's shotgun blast\n";
                                break;
                            default:
                                deathstring = "%s chewed on %s's boomstick\n";
                                break;
                        }
                        break;
                    case DMSG_SSHOTGUN:
                        switch ( attacker->playerclass )
                        {

                            case PC_SOLDIER:
                                deathstring = "%s was turned into swiss cheese by %s's buckshot\n";
                                break;
                            case PC_MEDIC:
                                deathstring = "%s got a double-dose of %s's buckshot\n";
                                break;
                            case PC_HVYWEAP:
                                deathstring = "%s unfortunately forgot %s carried a super-shotgun\n";
                                break;
                            case PC_SPY:
                                deathstring = "%s gets ventilated by %s's super-shotgun blast\n";
                                break;
                            case PC_ENGINEER:
                                deathstring = "%s's body got chuck full of %s's lead pellets\n";
                                break;
                            default:
                                deathstring = "%s ate 2 loads of %s's buckshot\n";
                                break;
                        }
                        break;
                    case DMSG_NAILGUN:
                        switch ( attacker->playerclass )
                        {
                            case PC_SCOUT:
                                deathstring = "%s caught one too many nails from %s\n";
                                break;
                            case PC_SNIPER:
                                deathstring = "%s ran into %s's nails\n";
                                break;
                            case PC_SPY:
                                deathstring = "%s was turned into %s's pin-cushion\n";
                                break;
                            default:
                                deathstring = "%s was nailed by %s\n";
                                break;
                        }
                        break;
                    case DMSG_SNAILGUN:
                        deathstring = "%s was punctured by %s\n";
                        break;
                    case DMSG_LIGHTNING:
                        if ( attacker->s.v.waterlevel > 1 )
                            deathstring = "%s accepts %s's discharge\n";
                        else
                            deathstring = "%s accepts %s's shaft\n";
                        break;
                    case DMSG_HOOK:
                        deathstring = "%s grappled with %s\n";
                        break;
                    case DMSG_SNIPERRIFLE:
                        if ( rnum <= 0.3 )
                        {
                            deathstring = "%s takes a bullet in the chest from %s\n";
                        } else
                        {
                            deathstring = "%s succumbs to sniperfire from %s\n";
                        }
                        break;
                    case DMSG_SNIPERHEADSHOT:
                        if ( rnum <= 0.5 )
                        {
                            deathstring = "%s gets a third eye from %s\n";
                        } else
                        {
                            deathstring = "%s gets his head blown off by %s\n";
                        }
                        break;
                    case DMSG_SNIPERLEGSHOT:
                        if ( rnum <= 0.5 )
                        {
                            deathstring = "%s is made legless by %s\n";
                        } else
                        {
                            deathstring = "%s gets his legs blown off by %s\n";
                        }
                        break;
                    case DMSG_AUTORIFLE:
                        deathstring = "%s collects %s's bullet spray.\n";
                        break;
                    case DMSG_ASSAULTCANNON:
                        deathstring = "%s gets sawn in half by %s\n";
                        break;
                    case DMSG_BACKSTAB:
                        deathstring = "%s gets knifed from behind by %s\n";
                        break;
                    case DMSG_TRANQ:
                        deathstring = "%s is put to sleep by %s\n";
                        break;
                    case DMSG_LASERBOLT:
                        deathstring = "%s gets a hole in his heart from %s's railgun\n";
                        break;
                    case DMSG_INCENDIARY:
                        deathstring = "%s gets well done by %s's incendiary rocket\n";
                        break;
                    case DMSG_SG_EXPLODION:
                        deathstring = "%s gets destroyed by %s's exploding sentrygun\n";
                        break;
                    case DMSG_DISP_EXPLODION:
                        deathstring = "%s didn't insert the correct change into %s's dispenser.\n";
                        break;

                }
                G_bprint( 1, deathstring, targ->s.v.netname, attacker->s.v.netname );
            }
        }
        return;
    }           //end of player vs player
    else
    {
        if ( streq( attacker->s.v.classname, "building_sentrygun" ) )
        {
            if ( targ == attacker->real_owner )
            {
                if ( tf_data.deathmsg == DMSG_SENTRYGUN_ROCKET )
                    deathstring = "%s intercepts his sentry gun's rocket\n";
                else
                {
                    if ( tf_data.deathmsg == DMSG_SENTRYGUN_BULLET )
                        deathstring = "%s crossed his sentry gun's line of fire\n";
                }
                G_bprint( 1, deathstring, targ->s.v.netname );
            } else
            {
                if ( teamplay && attacker->team_no == targ->team_no && attacker->team_no > 0 )
                {
                    G_bprint( 1, "%s obstructs his team's sentry gun\n", targ->s.v.netname );
                } else
                {
                    logfrag( attacker->real_owner, targ );
                    if ( tf_data.deathmsg == DMSG_SENTRYGUN_ROCKET )
                    {
                        deathstring = "%s hates %s's sentry gun\n";
                    } else
                    {
                        if ( tf_data.deathmsg == DMSG_SENTRYGUN_BULLET )
                        {
                            deathstring = "%s is mown down by %s's sentry gun\n";
                        }
                    }
                    G_bprint( 1, deathstring, targ->s.v.netname,
                            attacker->real_owner->s.v.netname );
                }
            }
        } else
        {
            logfrag( targ, targ );
            rnum = targ->s.v.watertype;
            switch ( ( int ) targ->s.v.watertype )
            {
                case -3:
                    if ( tfset(birthday) )
                    {
                        if ( g_random() < 0.5 )
                            deathstring = "%s bobs for apples\n";
                        else
                            deathstring = "%s drowns in the punch\n";
                    } else
                    {
                        if ( g_random() < 0.5 )
                            deathstring = "%s sleeps with the fishes\n";
                        else
                            deathstring = "%s sucks it down\n";
                    }
                    break;
                case -4:
                    if ( g_random() < 0.5 )
                        deathstring = "%s gulped a load of slime\n";
                    else
                        deathstring = "%s can't exist on slime alone\n";
                    break;
                case -5:
                    if ( targ->s.v.health < -15 )
                        deathstring = "%s burst into flames\n";
                    else
                    {
                        if ( g_random() < 0.5 )
                            deathstring = "%s turned into hot slag\n";
                        else
                            deathstring = "%s visits the Volcano God\n";
                    }
                    break;
                default:
                    if ( streq( attacker->s.v.classname, "explo_box" ) )
                    {
                        deathstring = "%s blew up\n";
                        break;
                    }
                    if ( attacker->s.v.solid == 4 && attacker != world )
                    {
                        deathstring = "%s was squished\n";
                        break;
                    }
                    if ( streq( targ->deathtype, "falling" ) )
                    {
                        targ->deathtype = "";
                        deathstring = "%s fell to his death\n";
                        break;
                    }
                    if ( streq( attacker->s.v.classname, "trap_shooter" )
                            || streq( attacker->s.v.classname, "trap_spikeshooter" ) )
                    {
                        deathstring = "%s was spiked\n";
                        break;
                    }
                    if ( streq( attacker->s.v.classname, "fireball" ) )
                    {
                        deathstring = "%s ate a lavaball\n";
                        break;
                    }
                    if ( streq( attacker->s.v.classname, "trigger_changelevel" ) )
                        deathstring = "%s tried to leave\n";
                    else
                        deathstring = "%s died\n";

                    break;

            }
            G_bprint( 1, deathstring, targ->s.v.netname );
        }
    }
}


void SpyUpFrames()
{
    int start, end;
    self->s.v.think = ( func_t ) _spy_up;
    self->s.v.nextthink = g_globalvars.time + 0.1;
    // Check .weapon, because .current_weapon has been reset
    if ( self->s.v.weapon <= 16 )
    {
        //	spy_upaxe1(  );
        start = 49; end = 41;
    }else{
        switch ( ( int ) ( g_random(  ) * 4 ) )
        {
            case 0:
                //spy_upb1(  );
                start = 69; end = 61;
                break;
            case 1:
                //spy_upc1(  );
                start = 84; end = 70;
                break;
            case 2:
                //spy_upd1(  );
                start = 95; end = 85;
                break;
            default:
                //spy_upe1(  );
                start = 102; end = 94;
                break;
        }
    }
    self->frame_info.end = end;
    self->frame_info.start = start;
}

void TeamFortress_SpyFeignDeath( int issilent )
{
    int     i, j;
    gedict_t *at_spot;
    gedict_t *te;

    self->StatusRefreshTime = g_globalvars.time + 0.1;
    if ( self->is_feigning )
    {
        // Check to make sure there isn't anyone on top of us
        at_spot = trap_findradius( world, self->s.v.origin, 64 );
        i = 1;
        j = 0;
        while ( at_spot )
        {
            if ( streq( at_spot->mdl, "progs/detpack.mdl" ) )
                j = 1;
            if ( streq( at_spot->mdl, "progs/detpack2.mdl" ) && tfset(birthday) )
                j = 1;
            if ( streq( at_spot->mdl, "progs/turrbase.mdl" ) )
                j = 1;
            if ( streq( at_spot->mdl, "progs/turrgun.mdl" ) )
                j = 1;
            if ( streq( at_spot->mdl, "progs/disp.mdl" ) )
                j = 1;
            if ( streq( at_spot->s.v.classname, "player" ) && !at_spot->s.v.deadflag && self != at_spot )
                j = 2;
            switch ( j )
            {
                case 1:
                    G_sprint( self, 2, "You can't get up with something\non top of you.\n" );
                    return;
                case 2:
                    G_sprint( self, 2, "You can't get up while someone\nis standing on you.\n" );
                    return;
            }
            at_spot = trap_findradius( at_spot, self->s.v.origin, 64 );
        }
        SetVector( self->s.v.velocity, 0, 0, 0 );
        setsize( self, -16, -16, -24, 16, 16, 32 );
        SetVector( self->s.v.view_ofs, 0, 0, 22 );
        self->s.v.movetype = MOVETYPE_WALK;
        self->is_feigning = 0;
        self->current_weapon = self->s.v.weapon;
        W_SetCurrentAmmo(  );
        self->tfstate = self->tfstate - ( self->tfstate & TFSTATE_CANT_MOVE );
        TeamFortress_SetSpeed( self );
        SpyUpFrames();
        return;
    } else  // !self->is_feigning
    {

        if ( self->hook_out )
        {
            G_sprint( self, 2, "You can't feign with the hook out.\n" );
            return;
        }
        //REMOVE!!!		
        /*          if (self.is_unabletospy == 1) {
                    G_sprint(self, 2, "You can't go undercover right now.\n");
                    return;
                    }*/

        /*  if (!(self.flags & 512) && !self->s.v.waterlevel) {
            G_sprint(self, 2, "You can't feign in the air.\n");
            return;
            }*/

        for ( at_spot = world; ( at_spot = trap_findradius( at_spot, self->s.v.origin, 64 ) ) ; )
        {
            if ( streq( at_spot->s.v.classname, "player" ) && self != at_spot && at_spot->is_feigning == 1 )
            {
                G_sprint( self, 2, "You can't feign on top of another spy!\n" );
                return;
            }
        }
        self->tfstate = self->tfstate | TFSTATE_CANT_MOVE;
        TeamFortress_SetSpeed( self );
        self->is_feigning = 1;
        Attack_Finished( 0.8 );
        self->invisible_finished = 0;
        self->s.v.modelindex = modelindex_player;
        self->s.v.weapon = self->current_weapon;
        self->current_weapon = 0;
        self->s.v.weaponmodel = "";
        self->s.v.weaponframe = 0;
        setsize( self, -16, -16, -24, 16, 16, -16 );
        SetVector( self->s.v.view_ofs, 0, 0, 4 );
        self->s.v.movetype = MOVETYPE_TOSS;
        if ( !issilent )
            DeathSound(  );
        self->s.v.angles[0] = 0;
        self->s.v.angles[2] = 0;
        TeamFortress_PlayerLostFlag();
        PlayerSetDieFrames(0);
        SpyFeignDeathNotes(self, self->last_attacker);
    }
}

//=========================================================================
// If its a net game, the SPY goes invisible.
// If its a LAN game, the class/skin changing menu pops up.
void TeamFortress_SpyGoUndercover(  )
{
    gedict_t *te;


    if ( tfset(invis_only) )
    {
        // If the spy is already invisible, become visible
        if ( ( int ) self->s.v.effects & ( EF_DIMLIGHT | EF_BRIGHTLIGHT ) )
        {
            G_sprint( self, 1, "You cannot disguise while glowing.\n" );
            return;
        }
        if ( self->is_unabletospy == 1 )
        {
            G_sprint( self, 2, "You can't go undercover right now.\n" );
            return;
        }
        if ( self->is_undercover == 1 )
        {
            self->is_undercover = 0;
            self->s.v.modelindex = modelindex_player; // return to normal
            self->s.v.items = ( int ) self->s.v.items - ( ( int ) self->s.v.items & IT_INVISIBILITY );
        } else
        {
            if ( self->is_undercover == 2 )
            {
                G_sprint( self, 2, "You stop going undercover.\n" );
                self->is_undercover = 0;
            } else
            {
                if ( self->s.v.ammo_cells > 1 )
                {
                    G_sprint( self, 2, "Going undercover...\n" );
                    self->is_undercover = 2;
                    te = spawn(  );
                    te->s.v.classname = "timer";
                    te->s.v.owner = EDICT_TO_PROG( self );
                    te->s.v.think = ( func_t ) TeamFortress_SpyUndercoverThink;
                    te->s.v.nextthink = g_globalvars.time + 4;
                }
            }
        }
        self->StatusRefreshTime = g_globalvars.time + 0.1;
    } else
    {
        if ( self->is_undercover != 2 )
        {
            self->current_menu = MENU_SPY;
            self->menu_count = MENU_REFRESH_RATE;
        } else
        {
            G_sprint( self, 2, "You stop going undercover.\n" );
            self->is_undercover = ( self->undercover_team || self->undercover_skin) ? 1 : 0;
        }
    }
}

//=========================================================================
// Try and find the player's name who's skin and team closest fit the 
// current disguise of the spy
void TeamFortress_SpyCalcName( gedict_t * spy )
{
    gedict_t *te;

    spy->undercover_name = NULL;
    // Find a player on the team the spy is disguised as to pretend to be
    if ( spy->undercover_team )
    {
        for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
        {
            // First, try to find a player with same color and skins
            if ( te->team_no == spy->undercover_team && te->s.v.skin == spy->undercover_skin )
            {
                spy->undercover_name = te->s.v.netname;
                break;
            }
        }
        // If we couldn't, just find one of that team
        if ( !spy->undercover_name )
        {

            for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
            {
                if ( te->team_no == spy->undercover_team )
                {
                    spy->undercover_name = te->s.v.netname;
                    break;
                }
            }
        }
    }
}

//=========================================================================
// Make the spy who owns this timer undercover, and then remove itself
void TeamFortress_SpyUndercoverThink(  )
{
    gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

    if ( owner->playerclass != PC_SPY )
        return;
    if ( owner->is_undercover == 2 )
    {
        if ( tfset(invis_only) )
        {
            owner->s.v.items = ( int ) owner->s.v.items | IT_INVISIBILITY;
            owner->s.v.frame = 0;
            owner->s.v.modelindex = modelindex_eyes;
            owner->is_undercover = 1;
        } else
        {
            owner->immune_to_check = g_globalvars.time + tfset_cheat_pause;	//10;
            if ( self->s.v.skin )
            {
                owner->undercover_skin = self->s.v.skin;
                TeamFortress_SetSkin( owner );
                G_sprint( owner, 2, "Skin set to " );
                TeamFortress_PrintClassName( owner, self->s.v.skin, 0 );
            }
            if ( self->s.v.team )
            {
                owner->undercover_team = self->s.v.team;
                TeamFortress_SetColor( owner, TeamFortress_TeamGetTopColor( self->s.v.team ),
                        TeamFortress_TeamGetColor( self->s.v.team ) - 1 );

                TeamFortress_SetSkin( owner );
                G_sprint( owner, 2, "Colors set to Team %.0f\n", self->s.v.team );
            }
            TeamFortress_SpyCalcName( owner );
            if ( !owner->StatusBarSize )
                G_centerprint( owner, "You are now disguised.\n" );
            owner->is_undercover = 1;
        }
    }
    owner->StatusRefreshTime = g_globalvars.time + 0.1;
    dremove( self );
}

//=========================================================================
// Change the Spy's skin to the class they chose
void TeamFortress_SpyChangeSkin( int class )
{
    gedict_t *te;

    // If they're returning their skin to their Spy, just reset it
    if ( class == PC_SPY )
    {

        if ( self->undercover_skin == 0 )
        {
            G_sprint( self, 2, "Skin reset.\n" );
            return;
        }
        G_sprint( self, 2, "Skin reset.\n" );
        self->undercover_skin = 0;
        TeamFortress_SetSkin( self );
        if ( !self->undercover_team )
            self->is_undercover = 0;
        return;
    }
    G_sprint( self, 2, "Going undercover...\n" );
    self->is_undercover = 2;

    // Start a timer, which changes the spy's skin to the chosen one
    te = spawn(  );
    te->s.v.classname = "timer";
    te->s.v.owner = EDICT_TO_PROG( self );
    te->s.v.think = ( func_t ) TeamFortress_SpyUndercoverThink;
    te->s.v.nextthink = g_globalvars.time + 4;
    te->s.v.skin = class;
    TeamFortress_SetSkin( self );
}

//=========================================================================
// Change the Spy's color to that of the Team they chose
void TeamFortress_SpyChangeColor( int teamno )
{
    gedict_t *te;

    // If they're returning their color to their own team, just reset it
    if ( teamno == self->team_no )
    {

        if ( self->undercover_team == 0 )
        {
            G_sprint( self, 2, "Colors reset.\n" );
            return;
        }
        G_sprint( self, 2, "Colors reset.\n" );
        self->immune_to_check = g_globalvars.time + tfset_cheat_pause;	//10;
        self->undercover_team = 0;
        TeamFortress_SetColor( self, TeamFortress_TeamGetTopColor( self->team_no ),
                TeamFortress_TeamGetColor( self->team_no ) - 1 );

        if ( !self->undercover_skin )
            self->is_undercover = 0;
        TeamFortress_SetSkin( self );
        return;
    }
    G_sprint( self, 2, "Going undercover...\n" );

    self->is_undercover = 2;

    // Start a timer, which changes the spy's skin to the chosen one
    te = spawn(  );
    te->s.v.classname = "timer";
    te->s.v.owner = EDICT_TO_PROG( self );
    te->s.v.think = ( func_t ) TeamFortress_SpyUndercoverThink;
    te->s.v.nextthink = g_globalvars.time + 4;
    te->s.v.team = teamno;
}

//=========================================================================
// Gas Grenade touch function.
void GasGrenadeTouch(  )
{
    sound( self, 1, "weapons/bounce.wav", 1, 1 );
    if ( VectorCompareF( self->s.v.velocity, 0, 0, 0 ) )
        SetVector( self->s.v.avelocity, 0, 0, 0 );
}

//=========================================================================
// Gas grenade explosion. Throws up the particle cloud.
void GasGrenadeExplode(  )
{
    gedict_t *te;
    float   pos;

    // Check the pointcontents to prevent detpack outside the world
    pos = trap_pointcontents( PASSVEC3( self->s.v.origin ) );
    if ( pos == CONTENT_EMPTY )
    {
        te = spawn(  );
        te->s.v.think = ( func_t ) GasGrenadeMakeGas;
        te->s.v.nextthink = g_globalvars.time + 0.1;
        te->heat = 0;
        VectorCopy( self->s.v.origin, te->s.v.origin );
        te->s.v.owner = self->s.v.owner;
        te->team_no = PROG_TO_EDICT( self->s.v.owner )->team_no;
        te->s.v.weapon = 0;
    } else
    {
        // Make some bubbles :)
        for ( pos = 0; pos < 10; pos++ )
        {
            newmis = spawn_buble( self );

            newmis->s.v.touch = 0;
            newmis->s.v.velocity[2] = 10 + g_random(  ) * 20;
        }
    }
    dremove( self );
}

//=========================================================================
// Gas Grenade Gas function
void GasGrenadeMakeGas(  )
{
    gedict_t *te;
    gedict_t *timer;

    self->s.v.nextthink = g_globalvars.time + 0.75;
    for ( te = world; (te = trap_findradius( te, self->s.v.origin, 200 )); )
    {
        if ( streq( te->s.v.classname, "player" ) && !te->s.v.deadflag && te->has_disconnected != 1 )
        {
            tf_data.deathmsg = DMSG_GREN_GAS;
            TF_T_Damage( te, world, PROG_TO_EDICT( self->s.v.owner ), 10, TF_TD_IGNOREARMOUR | TF_TD_NOTTEAM, 0 );
            if ( te->tfstate & TFSTATE_HALLUCINATING )
            {
                for ( timer = world; (timer = trap_find( timer, FOFS( s.v.classname ), "timer" )); )
                {
                    if ( PROG_TO_EDICT( timer->s.v.owner ) != te )
                        continue;
                    if ( timer->s.v.think != ( func_t ) HallucinationTimer )
                        continue;
                    break;
                }
                if ( timer )
                {
                    timer->s.v.health = timer->s.v.health + 25;
                    if(!( tfset_new_gas & GAS_MASK_NEWGREN_TIMES))
                    {
                        if ( timer->s.v.health < 100 )
                            timer->s.v.health = 100;
                        timer->s.v.nextthink = g_globalvars.time + 0.5;
                    } else
                    {
                        if ( timer->s.v.health < 150 )
                            timer->s.v.health = 150;
                        timer->s.v.nextthink = g_globalvars.time + 0.3;
                    }

                    if( !( tfset_new_gas & GAS_MASK_ALLSPYS ) && (g_random() < SETGAS_IN_GAS_TIME))
                        SetGasSkins(te);
                }
            } else
            {
                if ( tfset_new_gas & GAS_MASK_PALETTE)
                {
                    stuffcmd( te, "v_cshift 50 25 50 -50\n" );
                    G_sprint( te, 2, "Far out man!\n" );
                } else
                    G_sprint( te, 2, "Run for cover! They're everywhere!\n" );
                te->tfstate = te->tfstate | TFSTATE_HALLUCINATING;
                timer = spawn(  );
                if( !(tfset_new_gas & GAS_MASK_NEWGREN_TIMES))
                    timer->s.v.nextthink = g_globalvars.time + 0.5;
                else
                    timer->s.v.nextthink = g_globalvars.time + 0.3;
                timer->s.v.think = ( func_t ) HallucinationTimer;

                SetGasSkins(te);

                timer->s.v.classname = "timer";
                timer->s.v.owner = EDICT_TO_PROG( te );
                if( !(tfset_new_gas & GAS_MASK_NEWGREN_TIMES))
                    timer->s.v.health = 100;
                else
                    timer->s.v.health = 150;
                timer->team_no = self->team_no;
            }
        }
    }
    self->heat = self->heat + 1;
    if ( self->heat == 1 )
    {
        TempEffectCoordPVS( self->s.v.origin, TE_TAREXPLOSION );
        return;
    }
    if ( self->heat <= 20 )
    {
        self->s.v.weapon = self->s.v.weapon + 1;
        if ( self->s.v.weapon == 1 )
        {
            vec3_t v;
            VectorCopy( self->s.v.origin, v); v[2] -= 24;
            TempEffectCoordPVS( v, TE_LAVASPLASH );
        } else
        {
            if ( self->s.v.weapon == 2 )
                self->s.v.weapon = 0;
        }
        return;
    }
    dremove( self );
}

void GasEffect1( gedict_t * owner )	//Random Temp Entites
{
    g_globalvars.msg_entity = EDICT_TO_PROG( owner );
    trap_WriteByte( MSG_ONE, SVC_TEMPENTITY );

    switch ( ( int ) ( g_random(  ) * 3 ) )
    {
        case 0:
            trap_WriteByte( MSG_ONE, TE_EXPLOSION );
            break;
        case 1:
            trap_WriteByte( MSG_ONE, TE_TAREXPLOSION );
            break;
        default:
            trap_WriteByte( MSG_ONE, TE_LAVASPLASH );
            break;
    }
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[2] );
    if( tfset_new_gas & GAS_MASK_NEWGREN_DMG)
        T_Damage( owner, owner, owner, 0 );
}

static const char   *gas_sounds[] = {
    "play weapons/r_exp3.wav\n",
    "play weapons/rocket1i.wav\n",
    "play weapons/sgun1.wav\n",
    "play weapons/guncock.wav\n",
    "play weapons/ric1.wav\n",
    "play weapons/ric2.wav\n",
    "play weapons/ric3.wav\n",
    "play weapons/spike2.wav\n",
    "play weapons/tink1.wav\n",
    "play weapons/grenade.wav\n",
    "play weapons/bounce.wav\n",
    "play weapons/shotgn2.wav\n",
    "play wizard/wattack.wav\n",
    "play items/r_item1.wav\n",
    "play items/r_item2.wav\n",
    "play weapons/lhit.wav\n",
    "play misc/r_tele1.wav\n",
    "play weapons/railgun.wav\n"
};

void GasEffect2( gedict_t * owner )	//sounds
{
    int     i;

    g_globalvars.msg_entity = EDICT_TO_PROG( owner );
    trap_WriteByte( MSG_ONE, SVC_TEMPENTITY );
    trap_WriteByte( MSG_ONE, TE_TELEPORT );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[2] );

    if ( !(tfset_new_gas & GAS_MASK_NEWGREN_EFFECTS))
        return;
    i = g_random(  ) * ( sizeof( gas_sounds ) / sizeof( gas_sounds[0] )  );
    stuffcmd( owner, gas_sounds[i] );
}

/*static const char   *gas_sounds2[] = {
  "play weapons/detpack.wav\n",
  "play weapons/turrset.wav\n",
  "play weapons/turrspot.wav\n",
  "play weapons/turridle.wav\n",
  "play weapons/sniper.wav\n",
  "play weapons/flmfire2.wav\n",
  "play weapons/flmgrexp.wav\n",
  "play misc/vapeur2.wav\n",
  "play weapons/asscan1.wav\n",
  "play weapons/asscan2.wav\n"
  };*/
void GasEffect3( gedict_t * owner )
{
    gedict_t *te;
    int     i;

    g_globalvars.msg_entity = EDICT_TO_PROG( owner );

    te = spawn(  );
    te->s.v.origin[0] = owner->s.v.origin[0] + g_random(  ) * 800 - 400;
    te->s.v.origin[1] = owner->s.v.origin[1] + g_random(  ) * 800 - 400;
    te->s.v.origin[2] = owner->s.v.origin[2];
    trap_WriteByte( MSG_ONE, SVC_TEMPENTITY );
    trap_WriteByte( MSG_ONE, TE_LIGHTNING2 );
    WriteEntity( MSG_ONE, te );
    trap_WriteCoord( MSG_ONE, te->s.v.origin[0] );
    trap_WriteCoord( MSG_ONE, te->s.v.origin[1] );
    trap_WriteCoord( MSG_ONE, te->s.v.origin[2] );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
    trap_WriteCoord( MSG_ONE, owner->s.v.origin[2] );
    dremove( te );

    if ( !(tfset_new_gas & GAS_MASK_NEWGREN_EFFECTS))
        return;
    i = g_random(  ) * ( sizeof( gas_sounds ) / sizeof( gas_sounds[0] ) );
    stuffcmd( owner, gas_sounds[i] );
}

void HallucinationTimer(  )
{
    gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

    self->s.v.health = self->s.v.health - 2.5;
    if ( owner->playerclass == PC_MEDIC )
        self->s.v.health = self->s.v.health - 2.5;
    if ( self->s.v.health <= 0 || owner->s.v.deadflag || owner->has_disconnected == 1 )
        owner->tfstate = owner->tfstate - ( owner->tfstate & TFSTATE_HALLUCINATING );
    if ( owner->s.v.deadflag || owner->has_disconnected == 1 )
    {
        ResetGasSkins( owner );
        dremove( self );
        return;
    }
    if ( !( owner->tfstate & TFSTATE_HALLUCINATING ) )
    {
        ResetGasSkins( owner );

        if ( tfset_new_gas & GAS_MASK_PALETTE) 
            stuffcmd( owner, "v_cshift; wait; bf\n" );
        G_sprint( owner, 2, "You feel a little better now.\n" );
        dremove( self );
        return;
    }
    if( !(tfset_new_gas & GAS_MASK_NEWGREN_TIMES))
        self->s.v.nextthink = g_globalvars.time + 0.5;
    else
        self->s.v.nextthink = g_globalvars.time + 0.3;

    if(!( tfset_new_gas & GAS_MASK_ALLSPYS ) && g_random()< SETGAS_TIMER_THINK)
        SetGasSkins(owner);
    //?????
    //        	self->s.v.nextthink = g_globalvars.time + 0.5;

    if ( g_random(  ) < 0.5 )
        KickPlayer( -10, owner );
    if ( tfset_new_gas & GAS_MASK_PALETTE)
    {
        stuffcmd( owner, "v_cshift %d %d %d -75\n", ( int ) ( g_random(  ) * 100 ),
                ( int ) ( g_random(  ) * 100 ), ( int ) ( g_random(  ) * 100 ) );
    }
    g_globalvars.msg_entity = EDICT_TO_PROG( owner );
    switch ( ( int ) ( g_random(  ) * 3 ) )
    {
        case 0:
            GasEffect1( owner );
            break;
        case 1:
            GasEffect2( owner );
            break;
        default:
            GasEffect3( owner );
            break;
    }
}

//=========================================================================
// Firing Function for the Tranquiliser Gun
void W_FireTranq(  )
{

    self->s.v.currentammo = --( self->s.v.ammo_shells );

    KickPlayer( -2, self );
    newmis = spawn(  );
    newmis->s.v.owner = EDICT_TO_PROG( self );
    newmis->s.v.movetype = MOVETYPE_FLYMISSILE;
    newmis->s.v.solid = SOLID_BBOX;
    trap_makevectors( self->s.v.v_angle );
    VectorCopy( g_globalvars.v_forward, newmis->s.v.velocity );
    VectorScale( g_globalvars.v_forward, 1500, newmis->s.v.velocity ); // Faster than a normal nail
    vectoangles( newmis->s.v.velocity, newmis->s.v.angles );
    newmis->s.v.touch = ( func_t ) T_TranqDartTouch;
    newmis->s.v.think = ( func_t ) SUB_Remove;
    newmis->s.v.nextthink = g_globalvars.time + 6;
    setmodel( newmis, "progs/spike.mdl" );
    setsize( newmis, 0, 0, 0, 0, 0, 0 );
    setorigin( newmis,
            self->s.v.origin[0] + g_globalvars.v_forward[0] * 8,
            self->s.v.origin[1] + g_globalvars.v_forward[1] * 8,
            self->s.v.origin[2] + g_globalvars.v_forward[2] * 8 + 16 );
}

//=========================================================================
// Touch Function for the Tranquiliser Darts
void T_TranqDartTouch(  )
{
    gedict_t *timer;

    if ( other->s.v.solid == SOLID_TRIGGER )
        return;
    if ( trap_pointcontents( PASSVEC3( self->s.v.origin ) ) == -6 )
    {
        dremove( self );
        return;
    }
    if ( other->s.v.takedamage )
    {
        spawn_touchblood( 9 );
        tf_data.deathmsg = DMSG_TRANQ;
        TF_T_Damage( other, self, PROG_TO_EDICT( self->s.v.owner ), 20, TF_TD_NOTTEAM, TF_TD_NAIL );
        if ( streq( other->s.v.classname, "player" ) &&
                !( other->team_no == PROG_TO_EDICT( self->s.v.owner )->team_no && ( teamplay & ( TEAMPLAY_HALFARMOR_DIRECT | TEAMPLAY_NODIRECT ) ) ) )
        {
            if ( other->tfstate & TFSTATE_TRANQUILISED )
            {

                for ( timer = world; (timer = trap_find( timer, FOFS( s.v.classname ), "timer" )); )
                {
                    if ( PROG_TO_EDICT( timer->s.v.owner ) != other )
                        continue;
                    if ( timer->s.v.think != ( func_t ) TranquiliserTimer )
                        continue;
                    break;
                }
                if ( timer )
                    timer->s.v.nextthink = g_globalvars.time + 15;
            } else
            {
                G_sprint( other, 2, "You feel tired...\n" );
                other->tfstate = other->tfstate | TFSTATE_TRANQUILISED;
                timer = spawn(  );
                timer->s.v.nextthink = g_globalvars.time + TRANQ_TIME;
                timer->s.v.think = ( func_t ) TranquiliserTimer;
                timer->s.v.classname = "timer";
                timer->s.v.owner = EDICT_TO_PROG( other );
                timer->team_no = PROG_TO_EDICT( self->s.v.owner )->team_no;
                TeamFortress_SetSpeed( other );
            }
        }
    } else
    {
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

//=========================================================================
// Think function for Tranquilisation.
// Just remove the player's tranquilisation.
void TranquiliserTimer(  )
{
    gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

    owner->tfstate -= owner->tfstate & TFSTATE_TRANQUILISED;
    TeamFortress_SetSpeed( owner );
    G_sprint( owner, 2, "You feel more alert now\n" );
    dremove( self );
}

// Reset spy skin and color or remove invisibility
void Spy_RemoveDisguise( gedict_t * spy )
{

    if ( tfset(invis_only) != 1 )
    {
        if ( spy->playerclass == PC_SPY )
        {
            if ( spy->undercover_team )
            {
                spy->immune_to_check = g_globalvars.time + tfset_cheat_pause;	//10;
                spy->undercover_team = 0;
                TeamFortress_SetColor( spy, TeamFortress_TeamGetTopColor( spy->team_no ),
                        TeamFortress_TeamGetColor( spy->team_no ) - 1 );

            }
            if ( spy->undercover_skin )
            {
                spy->immune_to_check = g_globalvars.time + tfset_cheat_pause;	//10;
                spy->undercover_skin = 0;
                spy->s.v.skin = 0;
            }
            spy->is_undercover = 0;
            self->StatusRefreshTime = g_globalvars.time + 0.1;
            TeamFortress_SetSkin( spy );
            TeamFortress_SpyCalcName( spy );
        }
    } else
    {
        if ( spy->is_undercover )
        {
            spy->is_undercover = 0;
            spy->s.v.modelindex = modelindex_player;
            if ( ( int ) spy->s.v.items & IT_INVISIBILITY )
            {
                spy->invisible_finished = 0;
                spy->invisible_time = 0;
                spy->s.v.items = ( int ) spy->s.v.items - IT_INVISIBILITY;
            }
            self->StatusRefreshTime = g_globalvars.time + 0.1;
        }
    }
}

///Fake Color Skin Setinfo
void ResetGasSkins( gedict_t*pl)
{
    gedict_t*te;
    int		entnum;
    char	st[20];

    if( !(tfset_new_gas & (GAS_MASK_COLOR | GAS_MASK_SKIN | GAS_MASK_ALLSPYS)) )
        return;

    if( pl->has_disconnected )
        return;

    if( !pl->has_fake_gas_setinfo )
        return;

    for( te = world; (te = trap_find( te, FOFS( s.v.classname), "player" ));)
    {
        if( te->has_disconnected )
            continue;

        entnum = NUM_FOR_EDICT(te) - 1;

        if( entnum > MAX_CLIENTS )
        {
            G_conprintf("ResetGasSkins: entnum > MAX_CLIENTS\n");
            continue;
        }

        g_globalvars.msg_entity = EDICT_TO_PROG( pl );

        if( tfset_new_gas & (GAS_MASK_COLOR|GAS_MASK_ALLSPYS) )
        {
            GetInfokeyString( te, "topcolor", NULL, st, sizeof(st), "");

            trap_WriteByte(MSG_ONE,SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"topcolor" );
            trap_WriteString(MSG_ONE, st);

            GetInfokeyString( te, "bottomcolor", NULL, st, sizeof(st), "");

            trap_WriteByte(MSG_ONE, SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"bottomcolor" );
            trap_WriteString(MSG_ONE, st);
        }

        if( tfset_new_gas & (GAS_MASK_SKIN|GAS_MASK_ALLSPYS) )
        {
            GetInfokeyString( te, "skin", NULL, st, sizeof(st), "");

            trap_WriteByte(MSG_ONE, SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"skin" );
            trap_WriteString(MSG_ONE, st);
        }
    }
}


void SetGasSkins( gedict_t*pl)
{
    gedict_t*te;
    int		entnum;
    int		rskin,rteam,rcol;
    char	st[20];

    if( !(tfset_new_gas & (GAS_MASK_COLOR | GAS_MASK_SKIN | GAS_MASK_ALLSPYS)) )
        return;

    if( pl->has_disconnected )
        return;

    pl->has_fake_gas_setinfo = 1;
    for( te = world; (te = trap_find( te, FOFS( s.v.classname), "player" ));)
    {

        entnum = NUM_FOR_EDICT(te) - 1;

        if( te->has_disconnected || te == pl)
            continue;

        if( entnum > MAX_CLIENTS )
        {
            G_conprintf("SetGasSkins: entnum > MAX_CLIENTS\n");
            continue;
        }

        g_globalvars.msg_entity = EDICT_TO_PROG( pl );
        if( tfset_new_gas & GAS_MASK_ALLSPYS)
        {
            rteam = pl->team_no%2 + 1;

            rcol = TeamFortress_TeamGetTopColor(rteam);
            _snprintf(st, sizeof(st), "%d",rcol);
            trap_WriteByte(MSG_ONE,SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"topcolor" );
            trap_WriteString(MSG_ONE, st);

            rcol = TeamFortress_TeamGetColor(rteam) - 1;
            _snprintf(st, sizeof(st), "%d",rcol);

            trap_WriteByte(MSG_ONE, SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"bottomcolor" );
            trap_WriteString(MSG_ONE, st);


            trap_WriteByte(MSG_ONE, SVC_SETINFO );
            trap_WriteByte(MSG_ONE, entnum );
            trap_WriteString(MSG_ONE,"skin" );
            trap_WriteString(MSG_ONE, TeamFortress_GetSkinByTeamClass(rteam, 8));
        }else
        {
            rteam = pl->team_no;

            if( ( tfset_new_gas & GAS_MASK_COLOR ) && g_random()< SETGAS_SETCOLOR)
            {
                if( tfset_new_gas & GAS_MASK_ALLCOLORS)
                {
                    rcol = g_random() * 16;
                }else
                {
                    if( tfset_new_gas & GAS_MASK_4COLORS)
                        rteam = g_random() * 4;
                    else
                        rteam = g_random() * number_of_teams;
                    rteam++;
                    rcol = TeamFortress_TeamGetTopColor( rteam  );
                }

                _snprintf(st, sizeof(st), "%d",rcol);
                trap_WriteByte(MSG_ONE,SVC_SETINFO );
                trap_WriteByte(MSG_ONE, entnum );
                trap_WriteString(MSG_ONE,"topcolor" );
                trap_WriteString(MSG_ONE, st);

                if( !(tfset_new_gas & GAS_MASK_ALLCOLORS))
                {
                    rcol = TeamFortress_TeamGetColor(rteam) - 1;
                    _snprintf(st, sizeof(st), "%d",rcol);
                }
                trap_WriteByte(MSG_ONE,SVC_SETINFO );
                trap_WriteByte(MSG_ONE, entnum );
                trap_WriteString(MSG_ONE,"bottomcolor" );
                trap_WriteString(MSG_ONE, st);
            }

            if( (tfset_new_gas & GAS_MASK_SKIN ) && g_random()<SETGAS_SETSKIN)
            {
                rskin = g_random() *9 +1;


                trap_WriteByte(MSG_ONE, SVC_SETINFO );
                trap_WriteByte(MSG_ONE, entnum );
                trap_WriteString(MSG_ONE,"skin" );
                trap_WriteString(MSG_ONE, TeamFortress_GetSkinByTeamClass(rteam, rskin) );
            }

        }

    }
}

