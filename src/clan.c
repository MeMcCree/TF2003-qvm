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
 *  $Id: clan.c,v 1.12 2006-11-21 16:41:57 AngelD Exp $
 */
#include "g_local.h"

extern int last_id;
void MatchTimer( qboolean force );
void PreMatch_Think(  )
{
    int     time_left;
    gedict_t *te;
    gedict_t *oldself;
    gedict_t *gren;

    time_left = ceil( tf_data.cb_prematch_time - g_globalvars.time );
    if ( time_left > 60 )
    {
        G_bprint( 2, "%d minutes left till Match begins.\n", time_left / 60 );
        if ( time_left < 120 )
            self->s.v.nextthink = g_globalvars.time + time_left - 60;
        else
            self->s.v.nextthink = g_globalvars.time + 60.0;
        return;
    }
    if ( time_left >= 59 )
    {
        G_bprint( 2, "1 minute left till Match begins.\n" );
        self->s.v.nextthink = g_globalvars.time + 30.0;
        return;
    }
    if ( time_left >= 29 )
    {
        G_bprint( 2, "30 seconds left till Match begins.\n" );
        self->s.v.nextthink = g_globalvars.time + 20.0;
        return;
    }
    if ( time_left > 1 )
    {
        UpdateCountdown(time_left);
        G_bprint( 2, "%d seconds.\n", time_left );
        self->s.v.nextthink = g_globalvars.time + 1.0;
        return;
    }
    //if ( time_left > 0 )
    if( tf_data.cb_prematch_time > g_globalvars.time )
    {
        UpdateCountdown(time_left);
        G_bprint( 2, "1 second.\n" );
        self->s.v.nextthink = g_globalvars.time + 1.0;
        return;
    }
/*  if( tf_data.cb_prematch_time > g_globalvars.time )
    {
        self->s.v.nextthink = g_globalvars.time + 0.5;
        return;
    }*/
    G_bprint( 2, "MATCH BEGINS NOW\n" );
    MatchTimer( true );
    if ( tfset(game_locked) )
        G_bprint( 2, "GAME IS NOW LOCKED\n" );
    teamscores[0] = teamscores[1] = teamscores[2] = teamscores[3] = teamscores[4] = 0;
    teamfrags[0] = teamfrags[1] = teamfrags[2] = teamfrags[3] = teamfrags[4] = 0;
//paranoid ?????????
    if( tf_data.cease_fire )    
    {
        G_bprint(2,"!!!BUG BUG BUG!!! tf_data.cease_fire != 0\n");
        tf_data.cease_fire = 0;
    }
    for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
    {
        oldself = self;
        self = te;
        if ( !self->tf_id )
        {
            last_id = last_id + 20 + g_random(  ) * 10;
            self->tf_id = g_random(  ) * 10 + last_id;
            stuffcmd( self, "setinfo tf_id %d\n", self->tf_id );
            G_sprint( self, 2, "Your Battle ID is %d\n", self->tf_id );
        }
        if ( self->hook_out )
        {
            Reset_Grapple( self->hook );
            Attack_Finished( 0.75 );
            self->hook_out = 1;
        }
        TeamFortress_RemoveTimers(  );
        self->s.v.frags = 0;
        self->real_frags = 0;
        for ( gren = world; (gren = trap_find( gren, FOFS( s.v.classname ), "grenade" )); )
        {
            if ( gren->s.v.owner == EDICT_TO_PROG( self ) )
                gren->s.v.nextthink = g_globalvars.time + 0.1;
        }
        
        TF_T_Damage( self, world, world, self->s.v.health + 1, TF_TD_IGNOREARMOUR, 0 );

        self = oldself;
    }
}

void TeamFortress_ShowIDs(  )
{
    gedict_t *te;
    float   got_one;

    if ( !self->team_no )
    {
        G_sprint( self, 2, "You aren't in a team.\n" );
        return;
    }
    got_one = 0;
    G_sprint( self, 2, "Existing Team Member IDs:\n" );
    for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
    {
        if ( te->team_no == self->team_no )
        {
            got_one = 1;
            G_sprint( self, 2, "%s : %d\n", te->s.v.netname, te->tf_id );
        }
    }
    if ( !got_one )
        G_sprint( self, 2, "NONE\n" );
    got_one = 0;
    G_sprint( self, 2, "Disconnected Team Member IDs:\n" );
    for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "ghost" )); )
    {
        if ( te->team_no == self->team_no )
        {
            got_one = 1;
            G_sprint( self, 2, "%d\n", te->tf_id );
        }
    }
    if ( !got_one )
        G_sprint( self, 2, "NONE\n" );

}

int _isDraw ( int no_teams, int teamfrags_q )
{
    int i;
    for( i = 2; i <= no_teams; i++ )
    {
    if( ( teamscores[1] != teamscores[i] && teamfrags_q ) 
         || ( teamfrags[1] != teamfrags[i] && !teamfrags_q ))
        return 0;
    }
    return 1;
}

void DumpClanScores(  )
{
    int     winners, no_teams = 0, printed = 0, ti = 0, teamfrags_q;
    int     t_pl[5], t_unacc[5], i;
    gedict_t *te;
    const char   *st;
    char st2[10];

    for ( i = 1; i <= 4; i++ )
    {
        if ( (t_pl[i] = TeamFortress_TeamGetNoPlayers( i ) ))
            no_teams++;
        t_unacc[i] = 0;
    }

    if ( no_teams < 2 )
        return;
    teamfrags_q = tfset_toggleflags & ( TFLAG_TEAMFRAGS | TFLAG_FULLTEAMSCORE );
    for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
    {
        if ( te->team_no <= 0 || te->team_no > 4 )
            continue;
        t_unacc[te->team_no] += te->real_frags;
    }
    for ( i = 1; i <= 4; i++ )
        t_unacc[i] = teamfrags[i] - t_unacc[i];

    winners = TeamFortress_TeamGetWinner(  );
    G_bprint( 2, "\n\n=------= MATCH RESULTS =------=\n" );


    if ( _isDraw( no_teams, teamfrags_q ))
        G_bprint( 2, " DRAW " );
    else
    {
    G_bprint( 2, "%s defeated ", GetTeamName( winners ) );
    for ( i = 1; i < 4; i++ )
    {
        if ( winners != i && t_pl[i] )
        {
        st = GetTeamName( i );
        if ( !printed )
            G_bprint( 2, "%s", st );
        else if ( printed == no_teams )
            G_bprint( 2, " and %s", st );
        else
            G_bprint( 2, ", %s", st );
        printed++;

        }
    }
    }
    G_bprint( 2, "\n\n" );

    GetSVInfokeyString( "dtf", "dont_tweak_frags", st2, sizeof( st2 ), "off" );
    if ( strcmp( st2, "on" ) )
    {
        if ( teamfrags_q )
        {
            for ( i = 1; i <= 4; i++ )
            {
                if ( t_pl[i] <= 0 )
                    continue;
                printed = teamscores[i] / t_pl[i];
                ti = teamscores[i] % t_pl[i];
                for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
                {
                    if ( te->team_no == i )
                        te->s.v.frags = printed;
                    if ( ti )
                    {
                        te->s.v.frags += 1;
                        ti--;
                    }
                }
            }
        } else
        {
            for ( i = 1; i <= 4; i++ )
            {
                if ( !( t_pl[i] > 0 && t_unacc[i] > 0 ) )
                    continue;
                printed = t_unacc[i] / t_pl[i];
                ti = t_unacc[i] % t_pl[i];
                for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
                {
                    if ( te->team_no == i )
                    {
                        te->s.v.frags += printed;
                        if ( ti )
                        {
                            te->s.v.frags += 1;
                            ti--;
                        }
                    }
                }

            }
        }
    }
    for ( i = 1; i <= 4; i++ )
    {
        if ( t_pl[i] <= 0 )
            continue;
        G_bprint( 2, "\n=------= TEAM%d RESULTS =------=\n", i );
        G_bprint( 2, "%d players.\n%d frags, %d unaccounted for.\n%d team score.\n\n",
              TeamFortress_TeamGetNoPlayers( i ), teamfrags[i], t_unacc[i], teamscores[i] );
    }

    for ( te = world; (te = trap_find( te, FOFS( s.v.classname ), "player" )); )
    {
        if ( te->settings_bits & TF_TAKE_SSHOT_MASK )
        {
            stuffcmd( te, "screenshot\n" );
        }
    }
    MatchTimer( true );
    dremove(self);
}

void MatchTimer( qboolean force )
{
    static float lasttime = 0;
    int     time_left;

    if ( !( tfset_toggleflags & TFLAG_FIRSTENTRY ) )
        return;

    if( !force && lasttime && ( ( g_globalvars.time - lasttime ) < 60 ))
    {
        return;
    }
    lasttime = g_globalvars.time;
    if ( tf_data.cb_prematch_time > g_globalvars.time )
    {//prematch
        localcmd("serverinfo status Countdown\n" );
/*          time_left = ceil(tf_data.cb_prematch_time - g_globalvars.time+0.5);
        if( time_left > 60 )
            localcmd("serverinfo status \"PM %d min left\"\n", time_left / 60);
        else
            localcmd("serverinfo status \"PM %d sec left\"\n", time_left );
*/          
        return;
    }
    if( !timelimit )
    {
        localcmd("serverinfo status \"no timelimit\"\n");
        return;
    }
    if( g_globalvars.time < timelimit )
    {
        time_left = ceil( timelimit - g_globalvars.time +0.5);
        if( time_left > 60 )
            localcmd("serverinfo status \"%d min left\"\n", time_left / 60);
        else
            localcmd("serverinfo status \"%d sec left\"\n", time_left );
        return;
    }
    localcmd("serverinfo status Standby\n");
}

void UpdateServerinfoScores()
{
    switch(number_of_teams)
    {
        case 2:
            localcmd("serverinfo score \"%d:%d\"\n", teamscores[1],teamscores[2]);
            break;
        case 3:
            localcmd("serverinfo score \"%d:%d:%d\"\n", teamscores[1],teamscores[2],teamscores[3]);
            break;
        case 4:
            localcmd("serverinfo score \"%d:%d:%d:%d\"\n", teamscores[1],teamscores[2],teamscores[3],teamscores[4]);
            break;
        default:
            return;
    }

}

void UpdateCountdown(int time_left) {
    gedict_t* te;
    for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
        CenterPrint(te, "Match begins in %d %s\n", time_left, (time_left != 1 ? "seconds" : "second"));
        stuffcmd(te, "play buttons/switch04.wav\n");
    }
}

char not_ready_str[] = {
    'n', 'o', 't', ' ', (char)242, (char)229, (char)225, (char)228, (char)249, '\n', 0
};
char ready_str[] = "ready    \n";
char padding_string[] = "                                ";

void PreMatchReady_Think() {
    gedict_t* te;
    char   bstmp[512];
    char   rstmp[512];
    char   line[64];
    int mxlen, oldlen;

    bstmp[0] = '\0';
    rstmp[0] = '\0';
    line[0] = '\0';
    if (tf_data.cb_prematch_time - g_globalvars.time) {
        mxlen = 0;
        for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
            CenterPrint(te, "\n");
            if (strlen(te->s.v.netname) > mxlen) {
                mxlen = strlen(te->s.v.netname);
            }
        }
        for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
            CenterPrint(te, "\n");
            _snprintf(line, sizeof(line), "%s", te->s.v.netname);
            oldlen = strlen(line);
            if (oldlen < mxlen) {
                padding_string[mxlen - oldlen] = '\0';
                strcat(line, padding_string);
                padding_string[mxlen - oldlen] = ' ';
            }
            strcat(line, "    ");
            strcat(line, (te->ready ? ready_str : not_ready_str));
            if (te->team_no == 1) {
                strcat(bstmp, line);
            }
            if (te->team_no == 2) {
                strcat(rstmp, line);
            }
        }
        for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
            G_centerprint(te, "Blue\n\n%s\nRed\n\n%s\n", bstmp, rstmp);
            te->StatusRefreshTime = g_globalvars.time + 1.5;
        }
    }
    self->s.v.nextthink = g_globalvars.time + 1;
}

void AttackDefendSecondRound() {
    tfset_flagoff(admode);

    ent = spawn();
    ent->s.v.classname = "prematch";
    ent->s.v.think = ( func_t ) PreMatch_Think;
    ent->s.v.nextthink = g_globalvars.time;
    ent->heat = 0;

    if (tfset(prematch_readymode)) {
        ent = spawn();
        ent->s.v.classname = "prematch_ready";
        ent->s.v.think = (func_t)PreMatchReady_Think;
        ent->s.v.nextthink = g_globalvars.time + 1;
    }
}

void ChangeReadyState(int state) {
    gedict_t* te, *prematch;
    int maxclients, readied_up;

    if (!tfset(prematch_readymode)) {
        return;
    }
    if (tf_data.cb_prematch_time - g_globalvars.time <= 0) {
        return;
    }
    if (self->team_no != 1 && self->team_no != 2) {
        return;
    }

    prematch = world;
    prematch = trap_find(prematch, FOFS(s.v.classname), "prematch");
    if (prematch->heat == 1) {
        return;
    }

    self->ready = state;
    maxclients = trap_cvar("maxclients");
    readied_up = 0;
    for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
        if (te->ready) {
            readied_up++;
        }
    }
    if (state == 1) {
        if (readied_up == maxclients) {
            for (te = world; (te = trap_find(te, FOFS(s.v.classname), "player"));) {
                G_centerprint(te, "Prepare to fight!\n", self->s.v.netname, readied_up, maxclients);
                te->StatusRefreshTime = g_globalvars.time + 1;
            }
            prematch->s.v.nextthink = g_globalvars.time;
            prematch->heat = 1;
            prematch = world;
            prematch = trap_find(prematch, FOFS(s.v.classname), "prematch_ready");
            if (prematch != world) {
                dremove(prematch);
            }
            if (tfset(admode)) {
                timelimit_ad = g_globalvars.time + timelimit - tfset_prematch_time * 60;
            } else {
                timelimit -= tf_data.cb_prematch_time - 10;
                trap_cvar_set_float("timelimit", (float)timelimit / 60.0f);
            }
            tf_data.cb_prematch_time = g_globalvars.time + 10;
        }
    }
}