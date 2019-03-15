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
 *  $Id: menu.c,v 1.27 2006-11-21 21:47:50 AngelD Exp $
 */
#include "g_local.h"
#include "sentry.h"

typedef struct menu_s{
	int     allowed_impulses;
	int     reset_impulse;
	int     display_time;
	void    ( *Display ) ( menunum_t );
	void    ( *Input ) ( int );
} menu_t;

void    Menu_NULL( menunum_t menu );
void    Menu_Team( menunum_t );
void    Menu_Team_Input( int );
void    Menu_Class( menunum_t );
void    Menu_Class_Input( int );
void    Menu_Drop( menunum_t );
void    Menu_Drop_Input( int );
void    Menu_Intro( menunum_t );
void    Menu_ClassHelp( menunum_t );
void    Menu_ClassHelp2( menunum_t );
void    Menu_ClassHelp_Input( int );
void    Menu_RepeatHelp( menunum_t );
void    Menu_Engineer( menunum_t );
void    Menu_Engineer_Input( int inp );
void    Menu_EngineerFix_Dispenser( menunum_t );
void    Menu_EngineerFix_Dispenser_Input( int inp );
void    Menu_EngineerFix_SentryGun( menunum_t );
void    Menu_EngineerFix_SentryGun_Input( int inp );
void    Menu_Dispenser( menunum_t );
void    Menu_Dispenser_Input( int inp );
void    Menu_Spy( menunum_t menu );
void    Menu_Spy_Input( int inp );
void    Menu_Spy_Skin( menunum_t menu );
void    Menu_Spy_Skin_Input( int inp );
void    Menu_Spy_Color( menunum_t menu );
void    Menu_Spy_Color_Input( int inp );
void    Menu_BirthDay( menunum_t menu );
void    Menu_BirthDay_Input( int inp );

void    TG_Main_Menu( menunum_t menu );
void    TG_Main_Menu_Input( int inp );
void    TG_SGOptions_Menu_Input( int inp );
void    TG_SGOptions_Menu( menunum_t menu );
void    TG_Detpack_Menu( menunum_t menu );
void    TG_Detpack_Menu_Input( int inp );
void    TG_Cheats_Menu( menunum_t menu );
void    TG_Cheats_Menu_Input( int inp );
void    TG_SavePosition_Menu( menunum_t menu );
void    TG_SavePosition_Menu_Input( int inp );
void    TG_SG_Fire_Menu_Input( int inp );
void    TG_SG_Fire_Menu( menunum_t menu );

const static menu_t menus[] = {
	{0, 0, 0, NULL, NULL},	//MENU_NULL,                      
	{0, 0, 0, NULL, NULL},	//MENU_DEFAULT,                 
	{31, 0, 0, Menu_Team, Menu_Team_Input},	//MENU_TEAM,                    
	{-1, 0, 0, Menu_Class, Menu_Class_Input},	//MENU_CLASS,                   
	{31, 5, 0, Menu_Drop, Menu_Drop_Input},	//MENU_DROP,                    
	{0, 0, 4, Menu_Intro, NULL},	//MENU_INTRO,                   
	{512, 0, 8, Menu_ClassHelp, Menu_ClassHelp_Input},	//MENU_CLASSHELP,                      
	{0, 0, 5, Menu_ClassHelp2, NULL},	//MENU_CLASSHELP2,              
	{0, 0, 5, Menu_RepeatHelp, NULL},	//MENU_REPEATHELP,              
	{0, 0, 0, Menu_NULL, NULL},	//MENU_PICKBINDS,                       
	{0, 0, 0, Menu_NULL, NULL},	//MENU_SHOWBINDS1,              
	{0, 0, 0, Menu_NULL, NULL},	//MENU_SHOWBINDS2,              
	{-1, 0, 0, Menu_Spy, Menu_Spy_Input},	//MENU_SPY,                     
	{-1, 0, 0, Menu_Spy_Skin, Menu_Spy_Skin_Input},	//MENU_SPY_SKIN,                        
	{-1, 0, 0, Menu_Spy_Color, Menu_Spy_Color_Input},	//MENU_SPY_COLOR,                       
	{-1, 0, 0, Menu_Engineer, Menu_Engineer_Input},	//MENU_ENGINEER,                        
	{-1, 0, 0, Menu_EngineerFix_Dispenser,
	 Menu_EngineerFix_Dispenser_Input},	//MENU_ENGINEER_FIX_DISPENSER,  
	{-1, 0, 0, Menu_EngineerFix_SentryGun,
	 Menu_EngineerFix_SentryGun_Input},	//MENU_ENGINEER_FIX_SENTRYGUN,
	{0, 0, 0, Menu_NULL, NULL},	//MENU_ENGINEER_FIX_MORTAR,     
	{-1, 0, 0, Menu_Dispenser, Menu_Dispenser_Input},	//MENU_DISPENSER,                       
	{-1, 0, 0, Menu_Class, Menu_Class_Input},	//MENU_CHANGECLASS              
	{0, 0, 0, Menu_NULL, NULL},	//21
	{0, 0, 0, Menu_NULL, NULL},	//22
	{-1, 0, 0, Menu_BirthDay, Menu_BirthDay_Input},	//MENU_BIRTHDAY1
	{-1, 0, 0, Menu_BirthDay, Menu_BirthDay_Input},	//MENU_BIRTHDAY2
	{-1, 0, 0, Menu_BirthDay, Menu_BirthDay_Input},	//MENU_BIRTHDAY3

	{-1, 0, 0, TG_Main_Menu, TG_Main_Menu_Input},
	{-1, 0, 0, TG_SGOptions_Menu, TG_SGOptions_Menu_Input},
	{-1, 0, 0, TG_Detpack_Menu, TG_Detpack_Menu_Input},
	{-1, 0, 0, TG_Cheats_Menu, TG_Cheats_Menu_Input},
	{-1, 0, 0, TG_SavePosition_Menu, TG_SavePosition_Menu_Input},
	{-1, 0, 0, TG_SG_Fire_Menu, TG_SG_Fire_Menu_Input},

	{0, 0, 0, NULL, NULL}
};

int     NUM_menus = sizeof( menus ) / sizeof( menus[0] );

void Player_Menu(  )
{

	if ( self->menu_count > MENU_REFRESH_RATE )
		self->menu_count = 0;
	else
	{
		self->menu_count++;
		return;
	}

	if ( self->current_menu <= MENU_CLASS /*MENU_DEFAULT */  )
	{
		if ( !self->team_no && teamplay && self->lives )
		{
			self->current_menu = MENU_TEAM;
		} else
		{
			if ( !self->playerclass && self->lives )
				self->current_menu = MENU_CLASS;
			else
			{
				self->current_menu = MENU_DEFAULT;
				return;
			}
		}
	}

	if ( self->current_menu >= NUM_menus )
	{
		self->current_menu = MENU_DEFAULT;
		return;
	}

	if ( self->current_menu == MENU_DEFAULT )
	{
		self->current_menu = MENU_NULL;
		return;
	}

	if ( menus[self->current_menu].Display )
		menus[self->current_menu].Display( self->current_menu );

	if ( menus[self->current_menu].display_time )
	{
		if ( self->menu_displaytime > menus[self->current_menu].display_time )
			self->current_menu = MENU_DEFAULT;
		else
			self->menu_displaytime++;
	}
}

void ResetMenu(  )
{
	if ( !self->StatusBarSize )
		CenterPrint( self, "\n" );
	else
		self->StatusRefreshTime = g_globalvars.time + 0.1;
	self->menu_count = MENU_REFRESH_RATE;
	self->current_menu = MENU_DEFAULT;
}

void Menu_Input( int impulse )
{
	int     ai;

	if ( menus[self->current_menu].Input == NULL )
		return;
	if ( menus[self->current_menu].reset_impulse == impulse )
	{
		ResetMenu(  );
		self->s.v.impulse = 0;
		return;
	}

	ai = menus[self->current_menu].allowed_impulses;

	if ( ai < 0 || ( ai & ( 1 << ( impulse ) ) ) )
	{
		menus[self->current_menu].Input( impulse );
	}
}

extern char *team_menu_string;
const char *team_menu_strings[] = {
	 "              ",
	_M1 " Team One  ",
	_M2 " Team Two  ",
	_M3 " Team Three",
	_M4 " Team Four ",
	_M5 " Auto Team ",
};

void Menu_Team( menunum_t menu )
{
	if ( ( tfset_toggleflags & TFLAG_AUTOTEAM ) && teamplay )
	{
		if ( TeamFortress_TeamPutPlayerInTeam(  ) )
			return;
	}

	if ( team_menu_string )
	{
		CenterPrint( self, "%s", team_menu_string );
		return;
	}
	if ( CTF_Map == 1 )
		CenterPrint( self,
			     "=== Choose Your Team ===\n\n"
			     _M1 " Blue Team           \n"
			     _M2 " Red Team            \n\n\n\n"
			     _M7 " Bind my keys for me!\n\n"
			     "For full details on this patch:\n"
			     "http://www.telefragged.com/teamfortress/\n" );
	else
	{
		if ( number_of_teams == 1 )
			CenterPrint( self, "=== Choose Your Team ===\n\n%s\n",
				     team_menu_strings[1] );
		else
			CenterPrint( self,
				     "=== Choose Your Team ===\n\n%s\n%s\n%s\n%s\n%s\n",
				     team_menu_strings[1], team_menu_strings[2],
				     team_menu_strings[( number_of_teams > 2 ) ? 3 : 0],
				     team_menu_strings[( number_of_teams > 3 ) ? 4 : 0],
				     team_menu_strings[5] );
	}

}

void Menu_Team_Input( int inp )
{

	if ( inp == 5 )
		TeamFortress_TeamPutPlayerInTeam(  );
	else
	{
		if ( inp <= number_of_teams && inp > 0 )
			TeamFortress_TeamSet( inp );
		else
		{
			if ( !number_of_teams && inp <= 4 )
				TeamFortress_TeamSet( inp );
		}
	}
	ResetMenu(  );
	self->s.v.impulse = 0;
}

const char *class_str = 
"=== Choose Your Class ===\n\n\n"
    _M1 " Scout   \n"
    _M2 " Sniper  \n" 
    _M3 " Soldier \n" 
    _M4 " Demoman \n" 
    _M5 " Medic   \n" 
    _M6 " HWGuy   \n"
    _M7 " Pyro    \n"
    "%s"
    _M9 " Engineer\n"
    "%s";
const char *class_spy = _M8 " Spy     \n";
const char *class_rpc = _M0 " RandomPC\n";
const char *class_bd = _M0 " The Birthday Boy\n";

void Menu_Class( menunum_t menu )
{
	gedict_t *AD;

	AD = trap_find( world, FOFS( s.v.classname ), "info_tfdetect" );
	if ( AD )
	{
		switch ( self->team_no )
		{
		case 1:
			if ( AD->s.v.noise1 )
			{
				CenterPrint( self, "%s", AD->s.v.noise1 );
				return;
			}
			break;
		case 2:
			if ( AD->s.v.noise2 )
			{
				CenterPrint( self, "%s", AD->s.v.noise2 );
				return;
			}
			break;
		case 3:
			if ( AD->s.v.noise3 )
			{
				CenterPrint( self, "%s", AD->s.v.noise3 );
				return;
			}
			break;
		case 4:
			if ( AD->noise4 )
			{
				CenterPrint( self, "%s", AD->noise4 );
				return;
			}
			break;
		}
	}
	if ( TeamFortress_TeamIsCivilian( self->team_no ) )
	{
		CenterPrint( self, "Your team can only be Civilians.\n" );
		return;
	}
    CenterPrint( self, class_str, tfset(spy_off)? "": class_spy, tfset(birthday) ? class_bd: class_rpc);
}

void Menu_Class_Input( int imp )
{
	int     new_class = 0;	//, opt;

	//char    st[10];

	if ( imp > 10 || imp < 1 )
		return;
	self->s.v.impulse = imp + TF_CHANGEPC;
	if ( self->playerclass )
		new_class = 1;
	TeamFortress_ChangeClass(  );
	ResetMenu(  );
	if ( self->playerclass && new_class != 1 )
	{

		if ( self->settings_bits & TF_CLASS_HELP_MASK )
			self->current_menu = MENU_CLASSHELP;
	}
	self->menu_displaytime = 0;
	self->s.v.impulse = 0;
}

#define AMMO_DROP_STR   _M1 " Shells                      \n" \
			            _M2 " Nails                       \n" \
			            _M3 " Rockets                     \n" \
			            _M4 " Cells                       \n" \
			            _M5 " Nothing                     \n\n" 
void Menu_Drop( menunum_t menu )
{
	if ( self->playerclass == PC_ENGINEER )
		CenterPrint( self, "Drop or Make:                   \n" AMMO_DROP_STR );
	else
		CenterPrint( self, "Drop:                           \n" AMMO_DROP_STR );
}

void    TeamFortress_DropAmmo( int type );
void Menu_Drop_Input( int inp )
{
	if ( inp > 0 && inp < 5 )
		TeamFortress_DropAmmo( inp );
	if ( inp > 0 && inp < 6 )
		ResetMenu(  );
	self->s.v.impulse = 0;
}

void Menu_Intro( menunum_t menu )
{
	char    st1[1024], st2[1024];

	if ( GetSVInfokeyString( "motd1", NULL, st1, sizeof( st1 ), "" ) )
	{
		GetSVInfokeyString( "motd2", NULL, st2, sizeof( st2 ), "" );
		CenterPrint( self, "%s\n%s", st1, st2 );
	} else
		CenterPrint( self, "Welcome to " _TF2003 "\n"
			     _BY_SD_ANGEL "\n"
			     "======================================\n"
			     "http://mtfl.sd.ru\n" );
}

#define WEAP_STR _W _E _A _P _O _N _S ":                     \n"
#define _PRESS8_ALIAS "\nPress " _8 " for alias help\n"
#define _WSG  _M1 " Shotgun                  \n" 
#define _WSSG _M2 " Super Shotgun            \n" 
#define _WNG  _M4 " Nailgun                  \n"
#define _WSR  _M2 " Sniper Rifle             \n"
#define _WAR  _M3 " Auto Rifle               \n"
#define _WRL  _M7 " Rocket Launcher          \n"
#define _WGL  _M6 " Grenade Launcher         \n"
#define _WPL  _M7 " Pipebomb Launcher        \n"
#define _W__      "                             \n"
#define _WMK  _M1 " Medikit/BioWeapon        \n"
#define _WSNG _M4 " Super Nailgun            \n"
#define _WASC _M7 " Assault Cannon           \n"
#define _WICC _M7 " Incendiary Cannon        \n"
#define _WKNF _M1 " Knife                    \n"
#define _WTRG _M2 " Tranquiliser Gun         \n"
#define _WFMT _M7 " Flamethrower             \n"
#define _WSPN _M1 " Spanner                  \n"
#define _WRLG _M2 " RailGun                  \n" 
#define _SCOUT _S _C _O _U _T
#define _SNIP _S _N _I _P _E _R 
#define _SOLD _S _O _L _D _I _E _R
#define _DEMO _D _E _M _O _L _I _T _I _O _N " " _M _A _N
#define _MEDIC _M _E _D _I _C
#define _HWGUY _H _E _A _W _Y " " _W _E _P _O _N _S " " _G _U _Y 
#define _PYRO _P _Y _R _O 
#define _SPY  _S _P _Y 
#define _ENG _E _N _G _I _N _E _E _R 

const char *classhelp1[] = {
	"",
	_SCOUT " Details:               \n\n" WEAP_STR _WSG _WNG _PRESS8_ALIAS,
    _SNIP  " Details:              \n\n" WEAP_STR _WSR _WAR _WNG _PRESS8_ALIAS, 
	_SOLD  " Details:             \n\n" WEAP_STR _WSG _WSSG _WRL _PRESS8_ALIAS,
    _DEMO  " Details:     \n\n" WEAP_STR _WSG _WGL _WPL _PRESS8_ALIAS,
    _MEDIC " Details:               \n\n" WEAP_STR _WMK _WSG _WSNG _PRESS8_ALIAS,
    _HWGUY " Details:   \n\n" WEAP_STR _WSG _WSSG _WASC _PRESS8_ALIAS,
    _PYRO  " Details:                \n\n" WEAP_STR _WSG _WFMT _WICC _PRESS8_ALIAS,
    _SPY   " Details:                 \n\n" WEAP_STR _WKNF _WTRG _WSSG _WNG _PRESS8_ALIAS,
    _ENG   " Details:            \n\n" WEAP_STR  _WSPN _WRLG _WSSG _PRESS8_ALIAS,
};
#define GREN_STR _G _R _E _N _A _D _E _S ":            \n"
#define SPEC_CMD_STR _S _P _E _C _I _A _L " " _C _O _M _M _A _N _D _S ":   \n"
const char *classhelp2[] = {
	"",
	GREN_STR "Flash Grenade       \nConcussion Grenade  \n\n" SPEC_CMD_STR "Scanner : scan10,scan30,scan50,autoscan\nScanner mode : scane,scanf    \n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nFlare               \n\n" SPEC_CMD_STR "autozoom : Toggle Rifle Autozooming\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nNail Grenade        \n\n" SPEC_CMD_STR "None\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nMirv Grenade        \n\n" SPEC_CMD_STR "The Detpack : +det5,+det20,+det50\nDetonate Pipebombs : detpipe  \n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nConcussion Grenade  \n\n" SPEC_CMD_STR "None\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nMirv Grenade        \n\n" SPEC_CMD_STR "None\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nNapalm Grenade      \n\n" SPEC_CMD_STR "None\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nHallucinogen Grenade\n\n" SPEC_CMD_STR "Go Undercover : disguise\nFeign Death : feign, sfeign\n\n" _PRESS8_ALIAS,
	GREN_STR "Hand Grenade        \nEMP Grenade         \n\n" SPEC_CMD_STR "Start Building : build   \nDestroy : detdispenser, detsentry\n" _PRESS8_ALIAS
};
char   *class_stuffcmd[] = {
	"",
	_SCOUT " Details:\n" WEAP_STR _WSG _WNG                 
        GREN_STR "   Flash\n   Concussion Grenade\n" SPEC_CMD_STR 
	    "Scanner : scan10,scan30,scan50,autoscan\nScanner mode : scane,scanf\n\n",
    _SNIP  " Details:\n" WEAP_STR _WSR _WAR _WNG            
        GREN_STR "   Hand Grenade\n   Flare\n\n" SPEC_CMD_STR
	    "  autozoom : Toggle Rifle Autozooming\n\n\n",
	_SOLD  " Details:\n" WEAP_STR _WSG _WSSG _WRL           
        GREN_STR "   Hand Grenade\n   Nail Grenade\n" SPEC_CMD_STR "   None\n\n\n",
    _DEMO  " Details:\n" WEAP_STR _WSG _WGL _WPL            
        GREN_STR "   Hand Grenade\n   Mirv Grenade\n" SPEC_CMD_STR
	    "   The Detpack : +det5,+det20,+det50\n   Detonate Pipebombs : detpipe\n\n\n",
    _MEDIC " Details:\n" WEAP_STR _WMK _WSG _WSNG           
        GREN_STR "   Hand Grenade\n   Concussion Grenade\n" SPEC_CMD_STR "   None\n\n\n",
    _HWGUY " Details:\n" WEAP_STR _WSG _WSSG _WASC          
        GREN_STR "   Hand Grenade\n   Mirv Grenade\n" SPEC_CMD_STR "   None\n\n\n",
    _PYRO  " Details:\n" WEAP_STR _WSG _WFMT _WICC          
        GREN_STR "   Hand Grenade\n   Napalm Grenade\n" SPEC_CMD_STR "   None\n\n\n",
    _SPY   " Details:\n" WEAP_STR _WKNF _WTRG _WSSG _WNG    
        GREN_STR "   Hand Grenade\n   Hallucinogenic Grenade\n" SPEC_CMD_STR
	    "   Go Undercover : disguise\n   Feign Death: feign, sfeign\n\n",
    _ENG   " Details:\n" WEAP_STR  _WSPN _WRLG _WSSG        
        GREN_STR "   Hand Grenade\n   EMP Grenade\n" SPEC_CMD_STR
	    "   Start Building : build\n   Destroy : detdispenser, detsentry\n\n"
};
void Menu_ClassHelp( menunum_t menu )
{
	if ( self->playerclass < 1 || self->playerclass > 9 )
		return;
	if ( self->menu_displaytime < 5 )
		CenterPrint( self, classhelp1[self->playerclass] );
	else
		CenterPrint( self, classhelp2[self->playerclass] );

	if ( self->menu_displaytime > menus[menu].display_time )
		G_sprint( self, 2, class_stuffcmd[self->playerclass] );
}

void Menu_ClassHelp_Input( int inp )
{
	if ( inp == 8 )
	{
		Menu_ClassHelp2( MENU_CLASSHELP2 );
		self->menu_count = MENU_REFRESH_RATE;
		self->current_menu = MENU_CLASSHELP2;
		self->menu_displaytime = 0;
		self->s.v.impulse = 0;
	}
}
void Menu_ClassHelp2( menunum_t menu )
{
	CenterPrint( self, "Commands:\n"
		     "inv       : Show inventory \n"
		     "+gren1    : Throw grenade 1\n"
		     "+gren2    : Throw Grenade 2\n"
		     "reload    : Force a reload \n" "dropammo  : drop some ammo \n\n" );

	if ( self->menu_displaytime > menus[menu].display_time )
		G_sprint( self, 2, class_stuffcmd[self->playerclass] );
}

void Menu_RepeatHelp( menunum_t menu )
{
	CenterPrint( self, "Press " _8 " to see this help again\n" );
	self->current_menu = MENU_DEFAULT;
}

const char *menu_eng_header = "Action:                           \n";
const char *menu_eng_builddisp = _M1 " Build Ammo&Armor Dispenser   \n";
const char *menu_eng_buildsentry = _M2 " Build Sentry Gun             \n";
const char *menu_eng_exit = _M5 " Nothing                      \n\n";
const char *menu_eng_detdisp = _M7 " Remotely Detonate Dispenser  \n";
const char *menu_eng_detsentry = _M8 " Remotely Detonate Sentry Gun \n";


void Menu_Engineer( menunum_t menu )
{
	const char *s_bdisp = "", *s_detdisp = "", *s_bsentry = "", *s_detsentry = "";

	if ( self->has_dispenser )
	{
		s_detdisp = menu_eng_detdisp;
		if ( tfset(tg_enabled) )
			s_bdisp = menu_eng_builddisp;
		else
			s_bdisp = "";
	} else
	{

		if ( ( self->s.v.ammo_cells < BUILD_COST_DISPENSER )
		     && !tfset(tg_enabled) )
			s_bdisp = "\n";
		else
			s_bdisp = menu_eng_builddisp;

		s_detdisp = "";
	}

	if ( self->has_sentry )
	{
		s_detsentry = menu_eng_detsentry;
		if ( tfset(tg_enabled) )
			s_bsentry = menu_eng_buildsentry;
		else
			s_bsentry = "";
	} else
	{
		if ( ( self->s.v.ammo_cells < BUILD_COST_SENTRYGUN )
		     && !tfset(tg_enabled) )
			s_bsentry = "\n";
		else
			s_bsentry = menu_eng_buildsentry;

		s_detsentry = "";
	}

	CenterPrint( self, "%s%s%s%s%s%s", menu_eng_header, s_bdisp, s_detdisp, s_bsentry,
		     s_detsentry, menu_eng_exit );
}

void Menu_Engineer_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		if ( !( ( int ) self->s.v.flags & FL_ONGROUND ) )
		{
			CenterPrint( self, "You can't build in the air!\n\n" );
			ResetMenu(  );
			self->s.v.impulse = 0;
			return;
		}
		if ( ( self->s.v.ammo_cells >= BUILD_COST_DISPENSER
		       && self->has_dispenser == 0 ) || tfset(tg_enabled) )
		{
			TeamFortress_Build( 1 );
			ResetMenu(  );
			self->s.v.impulse = 0;
		}
		break;
	case 2:
		if ( !( ( int ) self->s.v.flags & FL_ONGROUND ) )
		{
			CenterPrint( self, "You can't build in the air!\n\n" );
			ResetMenu(  );
			self->s.v.impulse = 0;
			return;
		}
		if ( ( self->s.v.ammo_cells >= BUILD_COST_SENTRYGUN
		       && self->has_sentry == 0 ) || tfset(tg_enabled) )
		{
			TeamFortress_Build( 2 );
			ResetMenu(  );
			self->s.v.impulse = 0;
		}
		break;
	case 7:
		if ( self->has_dispenser > 0 )
		{
			DestroyBuilding( self, "building_dispenser" );
			ResetMenu(  );
			self->s.v.impulse = 0;
		}
		break;
	case 8:
		if ( self->has_sentry > 0 )
		{
			DestroyBuilding( self, "building_sentrygun" );
			ResetMenu(  );
			self->s.v.impulse = 0;
		}
		break;
	case 5:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	}
}

void Menu_EngineerFix_Dispenser( menunum_t menu )
{
	CenterPrint( self, "Action:                            \n"
		     _M1 " Put Ammo into Dispenser     \n"
		     _M2 " Put Armor into Dispenser    \n"
		     _M3 " Repair Dispenser            \n"
		     _M4 " Dismantle Dispenser         \n"
		     _M5 " Nothing                     \n\n" );
}

int Engineer_Dispenser_Repair( gedict_t* disp);
int Engineer_Dispenser_Dismantle( gedict_t* disp );
void Menu_EngineerFix_Dispenser_Input( int inp )
{
	float   metalcost;
	float   am;

	if ( strneq( self->s.v.classname, "player" ) || !self->building
	     || self->building == world )
		return;

	switch ( inp )
	{
	case 1:
		am = 20 * 2;
		if ( am > self->s.v.ammo_shells )
			am = self->s.v.ammo_shells;
		if ( am > 400 - self->building->s.v.ammo_shells )
			am = 400 - self->building->s.v.ammo_shells;
		self->s.v.ammo_shells = self->s.v.ammo_shells - am;
		self->building->s.v.ammo_shells = self->building->s.v.ammo_shells + am;
		am = 20 * 2;
		if ( am > self->s.v.ammo_nails )
			am = self->s.v.ammo_nails;
		if ( am > 600 - self->building->s.v.ammo_nails )
			am = 600 - self->building->s.v.ammo_nails;
		self->s.v.ammo_nails = self->s.v.ammo_nails - am;
		self->building->s.v.ammo_nails = self->building->s.v.ammo_nails + am;
		am = 10 * 2;
		if ( am > self->s.v.ammo_rockets )
			am = self->s.v.ammo_rockets;
		if ( am > 300 - self->building->s.v.ammo_rockets )
			am = 300 - self->building->s.v.ammo_rockets;
		self->s.v.ammo_rockets = self->s.v.ammo_rockets - am;
		self->building->s.v.ammo_rockets = self->building->s.v.ammo_rockets + am;
		am = 10 * 2;
		if ( am > self->s.v.ammo_cells )
			am = self->s.v.ammo_cells;
		if ( am > 400 - self->building->s.v.ammo_cells )
			am = 400 - self->building->s.v.ammo_cells;
		self->s.v.ammo_cells = self->s.v.ammo_cells - am;
		self->building->s.v.ammo_cells = self->building->s.v.ammo_cells + am;
		break;
	case 2:
		am = 40 * 2;
		if ( am > self->s.v.armorvalue )
			am = self->s.v.armorvalue;
		if ( am > 500 - self->building->s.v.armorvalue )
			am = 500 - self->building->s.v.armorvalue;
		self->s.v.armorvalue = self->s.v.armorvalue - am;
		self->building->s.v.armorvalue = self->building->s.v.armorvalue + am;
		break;
	case 3:
        Engineer_Dispenser_Repair(self->building);
		break;
	case 4:
        Engineer_Dispenser_Dismantle(self->building);
		break;
	case 5:
		break;
	default:
		return;
		break;
	}
	ResetMenu(  );
	self->s.v.impulse = 0;
	self->building = world;
	bound_other_ammo( self );
    bound_other_armor( self );
	W_SetCurrentAmmo(  );

}


const char *menu_eng_fixsg_upgrade = _M2 " Upgrade Sentry Gun          \n";
const char *menu_eng_fixsg_static = _M7 " Make static                 \n";
const char *menu_eng_fixsg_nostatic = _M7 " Make no static              \n";
void Menu_EngineerFix_SentryGun( menunum_t menu )
{
    const char *s_upgrade = "\n", *s_static = "";

    if ( tfset(tg_enabled) )
    {
        if ( self->building->has_sentry )
            s_static = menu_eng_fixsg_nostatic;
        else
            s_static = menu_eng_fixsg_static;
    }
    if( tfset(old_spanner) ){
        if ( self->building->s.v.weapon < 3
                && ( self->s.v.ammo_cells >= BUILD_COST_SENTRYGUN || tfset(tg_enabled) ) )
            s_upgrade = menu_eng_fixsg_upgrade;

        CenterPrint( self, "Action:                            \n"
                _M1 " Put Ammo into Sentry Gun    \n"
                "%s"
                _M3 " Repair Sentry Gun           \n"
                _M4 " Dismantle Sentry Gun        \n"
                _M5 " Nothing                     \n\n"
                _M6 " Rotate SentryGun            \n" "%s", s_upgrade, s_static );
    }else{
        CenterPrint( self, "Action:                            \n"
                _M4 " Dismantle Sentry Gun        \n"
                _M5 " Nothing                     \n\n"
                _M6 " Rotate SentryGun            \n" "%s", s_static );
    }

}

int Engineer_SentryGun_Upgrade( gedict_t* gun );
int Engineer_SentryGun_Repair( gedict_t* gun );
int Engineer_SentryGun_InsertAmmo( gedict_t* gun );
int Engineer_SentryGun_Dismantle( gedict_t* gun );
void Menu_EngineerFix_SentryGun_Input( int inp )
{
	float   am;
	float   metalcost = 0;

	if ( !self->building->real_owner->has_sentry )
		return;

	if ( strneq( self->s.v.classname, "player" ) || self->building == world
	     || !self->building )
		return;

	switch ( inp )
	{
	case 1:
        Engineer_SentryGun_InsertAmmo(self->building);
        break;
	case 2:
        Engineer_SentryGun_Upgrade(self->building);
			break;
	case 3:
        Engineer_SentryGun_Repair(self->building);
        break;
	case 4:
        Engineer_SentryGun_Dismantle(self->building);
		break;
	case 6:
		G_sprint( self, 2, "Rotating 45 degrees to the left...\n" );
		self->building->waitmin = anglemod( self->building->waitmin + 45 );
		self->building->waitmax = anglemod( self->building->waitmax + 45 );
		break;
	case 7:
		if ( !tfset(tg_enabled) )
			return;
		self->s.v.impulse = 0;
		if ( self->building->has_sentry )
			self->building->has_sentry = 0;
		else
			self->building->has_sentry = 1;
		ResetMenu(  );
		break;
	default:
		return;
	}

	ResetMenu(  );
	self->s.v.impulse = 0;
	bound_other_ammo( self );
    bound_other_armor( self );
	W_SetCurrentAmmo(  );

}

void Menu_Dispenser( menunum_t menu )
{
	CenterPrint( self, "Use Dispenser:                     \n"
		     _M1 " Withdraw some ammo          \n"
		     _M2 " Withdraw some Armor         \n"
		     _M3 " Nothing                     \n\n" );
}

void Menu_Dispenser_Input( int inp )
{
	float   am, empty = 0;

	switch ( inp )
	{
	case 1:
		if ( !self->building->s.v.ammo_shells
		     && !self->building->s.v.ammo_nails
		     && !self->building->s.v.ammo_rockets
		     && !self->building->s.v.ammo_cells )
		{
			empty = 1;
			break;
		}
		am = self->maxammo_shells - self->s.v.ammo_shells;
		if ( am > self->building->s.v.ammo_shells )
			am = self->building->s.v.ammo_shells;

		self->building->s.v.ammo_shells = self->building->s.v.ammo_shells - am;
		self->s.v.ammo_shells = self->s.v.ammo_shells + am;

		am = self->maxammo_nails - self->s.v.ammo_nails;
		if ( am > self->building->s.v.ammo_nails )
			am = self->building->s.v.ammo_nails;

		self->building->s.v.ammo_nails = self->building->s.v.ammo_nails - am;
		self->s.v.ammo_nails = self->s.v.ammo_nails + am;
		am = self->maxammo_rockets - self->s.v.ammo_rockets;
		if ( am > self->building->s.v.ammo_rockets )
			am = self->building->s.v.ammo_rockets;
		self->building->s.v.ammo_rockets = self->building->s.v.ammo_rockets - am;
		self->s.v.ammo_rockets = self->s.v.ammo_rockets + am;
		am = self->maxammo_cells - self->s.v.ammo_cells;
		if ( am > self->building->s.v.ammo_cells )
			am = self->building->s.v.ammo_cells;
		self->building->s.v.ammo_cells = self->building->s.v.ammo_cells - am;
		self->s.v.ammo_cells = self->s.v.ammo_cells + am;
		break;
	case 2:
		if ( !self->building->s.v.armorvalue )
		{
			empty = 1;
			break;
		}
		am = self->maxarmor - self->s.v.armorvalue;
		if ( am > self->building->s.v.armorvalue )
			am = self->building->s.v.armorvalue;
		if ( !self->s.v.armortype )
		{
			self->s.v.armortype = 0.3;
			self->s.v.items = ( int ) self->s.v.items | IT_ARMOR1;
		}
		self->building->s.v.armorvalue -= am;
		self->s.v.armorvalue += am;
		break;
	case 3:
		break;
	default:
		return;

	}
	if ( empty )
		G_sprint( self, 2, "The dispenser is empty.\n" );

	ResetMenu(  );
	self->s.v.impulse = 0;
	self->building = world;
	self->building_wait = g_globalvars.time + 0.5;
	bound_other_ammo( self );
    bound_other_armor( self );
	W_SetCurrentAmmo(  );

}

const char *spy_menu_feign = _M3 " Start Feigning              \n"
                             _M4 " Silent Feign                \n";
const char *spy_menu_stop_feign = _M3 " Stop Feigning               \n";
const char *spy_menu_undecover  = _M1 " Change Skin                 \n"
                                  _M2 " Change Color                \n";

const char *spy_menu_reset_skin = _M5 " Reset Skin                  \n";
const char *spy_menu_reset_color = _M5 " Reset Color                 \n";
const char *spy_menu_reset_skin_color = _M5 " Reset Skin and Color        \n";
void Menu_Spy( menunum_t menu )
{
	const char *s_undercover = spy_menu_undecover, *s_feign = "", *s_reset = "";

	if ( self->is_feigning )
		s_feign = spy_menu_stop_feign;
	else
		s_feign = spy_menu_feign;

	if ( self->undercover_team && self->undercover_skin )
	{
		s_reset = spy_menu_reset_skin_color;
	} else
	{
		if ( self->undercover_skin )
			s_reset = spy_menu_reset_skin;

		if ( self->undercover_team )
			s_reset = spy_menu_reset_color;
	}


	if ( ( ( int ) self->s.v.effects & ( 8 | 4 ) ) || self->is_unabletospy == 1 )
	{
		s_undercover = "";
	}

	CenterPrint( self, "Action:                           \n"
		     "%s%s%s"
		     _M6 " Nothing                     \n\n",
		     s_undercover, s_feign, s_reset );
}

void Menu_Spy_Input( int inp )
{
	if ( inp == 1 || inp == 2 )
	{
		if ( ( int ) self->s.v.effects & ( EF_DIMLIGHT | EF_BRIGHTLIGHT ) )
		{
			G_sprint( self, 2, "You can't go undercover while glowing.\n" );
			ResetMenu(  );
			self->s.v.impulse = 0;
			return;
		}
		if ( self->is_unabletospy == 1 )
		{
			G_sprint( self, 2, "You can't go undercover right now.\n" );
			ResetMenu(  );
			self->s.v.impulse = 0;
			return;
		}
	}


	switch ( inp )
	{
	case 1:
		Menu_Spy_Skin( MENU_SPY_SKIN );
		self->menu_count = MENU_REFRESH_RATE;
		self->current_menu = MENU_SPY_SKIN;
		self->menu_displaytime = 0;
		self->s.v.impulse = 0;
		break;
	case 2:
		Menu_Spy_Color( MENU_SPY_COLOR );
		self->menu_count = MENU_REFRESH_RATE;
		self->current_menu = MENU_SPY_COLOR;
		self->menu_displaytime = 0;
		self->s.v.impulse = 0;
		break;
	case 3:
		TeamFortress_SpyFeignDeath( 0 );
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	case 4:
		if ( !self->is_feigning )
			TeamFortress_SpyFeignDeath( 1 );
		ResetMenu(  );
		self->s.v.impulse = 0;

		break;
	case 5:
		Spy_RemoveDisguise( self );
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	case 6:
		//if ( self->undercover_team || self->undercover_skin )
		{
			ResetMenu(  );
			self->s.v.impulse = 0;
		}
		break;
	}

}
void Menu_Spy_Skin( menunum_t menu )
{
	CenterPrint( self,
		     "Change Skin to:\n"
    _M1 " Scout   \n"
    _M2 " Sniper  \n" 
    _M3 " Soldier \n" 
    _M4 " Demoman \n" 
    _M5 " Medic   \n" 
    _M6 " HWGuy   \n"
    _M7 " Pyro    \n"
    _M8 " Spy     \n"
    _M9 " Engineer\n"
             "\n" );
}

void Menu_Spy_Skin_Input( int inp )
{
	if ( inp < 10 && inp > 0 )
	{
		TeamFortress_SpyChangeSkin( inp );
		ResetMenu(  );
		self->s.v.impulse = 0;
	}
}
void Menu_Spy_Color( menunum_t menu )
{
	if ( !number_of_teams )
	{
		G_sprint( self, 2, "No Color changing allowed in deathmatch.\n" );
		ResetMenu(  );
		self->s.v.impulse = 0;
		return;
	}
	CenterPrint( self,
		     "=== Change Color to the Same Color as  ===\n\n%s\n%s\n%s\n%s\n\n",
		     team_menu_strings[1],
		     team_menu_strings[( number_of_teams > 1 ) ? 2 : 0],
		     team_menu_strings[( number_of_teams > 2 ) ? 3 : 0],
		     team_menu_strings[( number_of_teams > 3 ) ? 4 : 0] );

}

void Menu_Spy_Color_Input( int inp )
{
	if ( inp >= 1 && inp <= number_of_teams )
	{
		TeamFortress_SpyChangeColor( inp );
		ResetMenu(  );
		self->s.v.impulse = 0;
	}
}

void Menu_NULL( menunum_t menu )
{
	self->current_menu = MENU_DEFAULT;
}


const char *birthday_msgs[] = {
	"\n\n\n\nHAPPY BIRTHDAY TEAMFORTRESS!\n",
	"\n\n\n\nCurrent number of Snipers on\nthe Battlements:\n%4d",
	"\n\n\n\nYeeha!\nThe 505,672nd detpack was\njust laid on the bridge!\n",
	"\n\n\n\nIs that an assault cannon in your\n pocket, or are you just playing TF?\n(Blame Ian)\n",
	"\n\n\n\n25,000 downloads\n50 donations\nDamn, but we rock!\n",
	"\n\n\n\nTeamFortress is one year old today!\n",
	"\n\n\n\nTF II available 2nd quarter 98\n",
	"\n\n\n\nhmm.... I wonder what the next\nmessage will be...\n",
	"\n\n\n\nKill your friends! Kill your family!\nSnipe your pets! Detpack your house!\nGet TF Now!\n",
	"\n\n\n\nDeath to Potatoes!\n",
	"\n\n\n\n\"You guys have really fucked up\n urinals, you know that?\"\n   - TyR in Australia\n",
	"\n\n\n\nMany potatoes were harmed in the\nmaking of this product.\n",
	"\n\n\n\nBAH! I shoulda put the Demoman\nblast armor back while I was at it!\n   - Gudlyf\n",
	"\n\n\n\nTwin Peaks will be out... uhh...\nerr... soon.\n",
	"\n\n\n\n\"Twin Peaks will be finished tomorrow.\"\n   - TyR, 16th July, 25th July, 2nd August...",
	"\n\n\n\n\"After all, TF is an INSULT to the\npurity of CTF!\"\n   - Mjollnir, who was joking... really!",
	"\n\n\n\n\"I force them to work.\nElse I cut back their supplies\"\n   - Vomitgod, on TFS\n",
	"\n\n\n\nI remember the good ol' days...\nwhen you had to use imin1 & imin2\nto join a team.\n",
	"\n\n\n\nI remember the good ol' days...\nwhen there were 2 TF servers...\nand they were always down.",
	"\n\n\n\nI remember the good ol' days...\nwhen no-one knew how to use\nhand grenades...\n",
	"\n\n\n\nI remember the good ol' days...\nwhen 2fort was the only TF map.\nWe sure have come a long\nway since then... sigh",
	"\n\n\n\nI remember the good ol' days...\nwhen the sniper rifle just\nkilled in one hit... everytime\n",
	"\n\n\n\nI remember the good ol' days...\nwhen I could download TF in\n1 minute 20 seconds\n",
	"\n\n\n\nI remember the good ol' days...\nwhen I didn't have to download\nANYTHING to play TF\n",
	"\n\n\n\nI remember the good ol' days...\nwhen players used to say\n\"What's that bubble?\"\n",
	"\n\n\n\nI remember the good ol' days...\nwhen The Well actually had a well...\n",
	"\n\n\n\nI remember the good ol' days...\nwhen the motion detector was officially\nthe Scout's best friend, at least\naccording to the readme.txt\n",
	"\n\n\n\nI remember the good ol' days...\nwhen  Ian went to jail for punching\nRobin out\n",
	"\n\n\n\nTF Newbie Quote #1:\nUmm... How do I set a detpack?\n",
	"\n\n\n\nTF Newbie Quote #2:\nUmm... How do I throw a grenade?\n",
	"\n\n\n\nTF Newbie Quote #3:\nHey, he is cheating, that soldier just jumped up to the roof!!\n",
	"\n\n\n\nTF Newbie Quote #4:\nHow do I throw the pins?\n",
	"\n\n\n\nTF Newbie Quote #5:\nWhere do I take the flag!?!?!\n",
	"\n\n\n\nTF Newbie Quote #6:\nWhere's the control room?\n",
	"\n\n\n\nTF Newbie Quote #7:\nWhy the hell are these backpacks\nexploding?\n",
	"\n\n\n\nTF Newbie Quote #8:\nWho's the maniac with the axe?\n",
	"\n\n\n\nTF Newbie Quote #9:\nStop shooting me!\nI'm on your team!\nYou tried to attack my with the axe!\n",
	"\n\n\n\nTF Newbie Quote #10:\nWhat's this key? I thought this\nwas a CTF style map, guys?\n",
	"\n\n\n\nTF Veteran Quote #1:\nUm, Red Medics, please don't\nheal the President.\n",
	"\n\n\n\nTF Veteran Quote #2:\nGuys could you NOT set up\nsentries in hunted?\n",
	"\n\n\n\nTF Veteran Quote #3:\nWho the hell is on\nthe lift?\n",
	"\n\n\n\nTF Veteran Quote #4:\nDISCARD!!\n",
	"\n\n\n\nTF Veteran Quote #5:\nDamn Snipers!\n",
	"\n\n\n\nTF Veteran Quote #6:\nDamn Snipers!\n",
	"\n\n\n\nTF Veteran Quote #7:\nGet a mask or\nget in the WATER!!\n",
	"\n\n\n\nTF Veteran Quote #8:\nSpy's, please change colors\noutside our base.\n",
	"\n\n\n\nTF Veteran Quote #9:\nI was typing!!\n",
	"\n\n\n\nTF Veteran Quote #10:\nWhy is that guy running\nout of our yard with\nthe flag???\n",
	"\n\n\n\nTF's original design docs!\nCheck it out!\nwww.teamfortress.com/files/teamfortress/tfdes_1.gif",
	"\n\n\n\nTF's original design docs!\nCheck it out!\nwww.teamfortress.com/files/teamfortress/tfdes_2.gif",
	"\n\n\n\n\"MJ: Did you hear John Cash wrote TF?\"\n   - VomitGod"
};
int     num_birthday_msgs = sizeof( birthday_msgs ) / sizeof( birthday_msgs[0] );
int     snipers_num;
void BirthdayTimer(  )
{
	int     rnum;
	gedict_t *te;

	if ( self->s.v.weapon > 5 )
	{
		self->s.v.weapon = 0;
		self->s.v.nextthink = g_globalvars.time + 180 + g_random(  ) * 60;
		rnum = ( int ) ( g_random(  ) * num_birthday_msgs );
		self->team_str_home = NULL;
		if ( rnum == 1 )
		{
			snipers_num = TeamFortress_GetNoPlayers(  ) / 2;
			snipers_num = snipers_num * ( g_random(  ) + 1 );
		}
		self->team_str_moved = ( char * ) birthday_msgs[rnum];
	} else
	{
		self->s.v.nextthink = g_globalvars.time + 1.5;
		self->s.v.weapon += 1;
	}
	for ( te = world; ( te = trap_find( te, FOFS( s.v.classname ), "player" ) ); )
	{
		G_centerprint( te, self->team_str_moved, snipers_num );
		if ( self->s.v.weapon == 1 )
			sound( te, 3, "misc/b1.wav", 1, 1 );
		else
		{
			if ( self->s.v.weapon <= 4 )
			{
				switch ( ( int ) ( g_random(  ) * 3 ) )
				{
				case 0:
					sound( te, 3, "misc/b2.wav", 1, 1 );
					break;
				case 1:
					sound( te, 3, "misc/b3.wav", 1, 1 );
					break;
				default:
					sound( te, 3, "misc/b4.wav", 1, 1 );
					break;
				}
			}
		}

	}
}

void Menu_BirthDay( menunum_t menu )
{
	if ( self->current_menu == MENU_BIRTHDAY2 )
		CenterPrint( self, "3rd Impulse\n" );
	else
	{
		if ( self->current_menu == MENU_BIRTHDAY3 )
			CenterPrint( self, "4th Impulse\n" );
	}

}

void Menu_BirthDay_Input( int inp )
{
	gedict_t *te;

	switch ( self->current_menu )
	{
	case MENU_BIRTHDAY1:
		ResetMenu(  );
		self->s.v.impulse = 0;
		if ( inp == 98 )
			self->current_menu = MENU_BIRTHDAY2;
		break;
	case MENU_BIRTHDAY2:
		ResetMenu(  );
		self->s.v.impulse = 0;
		if ( inp == 156 )
			self->current_menu = MENU_BIRTHDAY3;
		break;

	case MENU_BIRTHDAY3:
		ResetMenu(  );
		self->s.v.impulse = 0;
		if ( inp != 96 )
			break;
        tfset_flagon( birthday );
		//localcmd( "localinfo birthday on\n" );
		G_bprint( 2, "IT'S PARTY TIME\n" );
		for ( te = world;
		      ( te = trap_find( te, FOFS( s.v.classname ), "player" ) ); )
			CenterPrint( te, "\n\nHAPPY BIRTHDAY TEAMFORTRESS!\n" );
		te = spawn(  );
		te->s.v.weapon = 10;
		te->s.v.nextthink = g_globalvars.time + 60;
		te->s.v.think = ( func_t ) BirthdayTimer;
		break;
	}
}

void TG_Main_Menu( menunum_t menu )
{
	CenterPrint( self, "Options:\n"
		     _M1 " SG options                 \n"
		     _M2 " Detpack option             \n"
		     _M3 " Cheats                     \n"
		     _M4 " Load defaults              \n"
		     _M5 " Saved position             \n"
		     _M7 " Nothing                    \n" );
}

void TG_Main_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		self->current_menu = TG_MENU_SG;
		break;
	case 2:
		self->current_menu = TG_MENU_DETPACK;
		break;
	case 3:
		self->current_menu = TG_MENU_CHEATS;
		break;
	case 4:
		TG_LoadSettings(  );
		break;
	case 5:
		self->current_menu = TG_MENU_POSITION;
		break;
	case 7:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;

}

const char *sentry_sfire_names[] = {
	_M4 " Sentry Shells Fire: NEW    \n",
	_M4 " Sentry Shells Fire: 2.8.1  \n",
	_M4 " Sentry Shells Fire: MTFL1  \n",
	_M4 " Sentry Shells Fire: MTFL2  \n"
};

const char *sentry_find_names[] = {
	_M6 LED_G "ignore teammates           \n",
	_M6 LED_Y "ignore owner               \n",
	_M6 LED_B "ignore OFF                 \n",
	_M6 LED_R "ignore all targets         \n",
};

/*const char *sentry_firetype_names[] = {
	_M7  Fire bullets & rockets     \n",
	_M7  Fire bullets               \n",
	_M7  Fire lightning (no damage) \n"
};*/
void TG_SGOptions_Menu( menunum_t menu )
{
	const char *s_sg_newfind, *s_sg_sfire, *s_sg_find, *s_sgfiretype, *s_sbar,*s_sg_unlimit_ammo;
	char    s_sgppl[80];
	const char *s_sg_rfire;

	if ( tfset(sg_newfind) )
	{
		s_sg_newfind = _M1 LED_B "Sentry New Find Target ON  \n";
		_snprintf( s_sgppl, sizeof( s_sgppl ), "       %3d ppl emulation      \n",
			   tfset_sgppl );
	} else
	{
		s_sg_newfind = _M1 LED_R "Sentry New Find Target OFF \n";
		_snprintf( s_sgppl, sizeof( s_sgppl ), "\n" );
	}
	if ( tfset(sg_rfire) )
		s_sg_rfire = _M3 LED_B "Sentry Rocket Fire: NEW    \n";
	else
		s_sg_rfire = _M3 LED_R "Sentry Rocket Fire: OLD    \n";

	if ( tg_data.sg_unlimit_ammo )
		s_sg_unlimit_ammo = _M5 LED_B "Unlimited ammo ON          \n";
	else
		s_sg_unlimit_ammo = _M5 LED_R "Unlimited ammo OFF         \n";


	if ( tfset_sg_sfire >= SG_SFIRE_NUM )
		tfset_sg_sfire = 0;
	s_sg_sfire = sentry_sfire_names[tfset_sg_sfire];

	if ( tg_data.sg_allow_find >= TG_SG_FIND_IGNORE_NUM )
		tg_data.sg_allow_find = TG_SG_FIND_IGNORE_TEAM;

	s_sg_find = sentry_find_names[tg_data.sg_allow_find];

/*REMOVE!!!
  if(tg_data.sg_fire_type >= TG_SG_FIRE_NUM)
  	tg_data.sg_fire_type = TG_SG_FIRE_NORMAL;
  s_sgfiretype = sentry_firetype_names[tg_data.sg_fire_type];*/
	s_sgfiretype = _M7 " Fire type                  \n";
	if ( tg_data.tg_sbar )
		s_sbar = _M8 LED_B "Eng Sbar for All           \n";
	else
		s_sbar = _M8 LED_R "Limited Eng Sbar           \n";

	CenterPrint( self, "Sentry Gun Options:\n"
		     "%s%s%s%s"
		     "%s%s%s%s"
		     _M9 " Nothing                    \n",
		     s_sg_newfind, s_sgppl, s_sg_rfire, s_sg_sfire,
		     s_sg_unlimit_ammo, s_sg_find, s_sgfiretype, s_sbar );
}
void TG_SGOptions_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
        tfset_flagtoggle( sg_newfind );
		break;
	case 3:
        tfset_flagtoggle( sg_rfire );
		break;
	case 4:
		if ( ++( tfset_sg_sfire ) >= SG_SFIRE_NUM )
			tfset_sg_sfire = 0;
		break;
	case 5:
	        tg_data.sg_unlimit_ammo = ( tg_data.sg_unlimit_ammo ) ? false : true;
		break;
	case 6:
		if ( ++( tg_data.sg_allow_find ) >= TG_SG_FIND_IGNORE_NUM )
			tg_data.sg_allow_find = 0;
		break;
	case 7:
		self->current_menu = TG_MENU_SG_FIRE;
/*			if( ++(tg_data.sg_fire_type) >= TG_SG_FIRE_NUM)
				tg_data.sg_fire_type = 0;*/

		break;
	case 8:
		tg_data.tg_sbar = ( tg_data.tg_sbar ) ? 0 : 1;
		break;
	case 9:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;
}

void TG_SG_Fire_Menu( menunum_t menu )
{
	const char *s_sg_firebullets, *s_sg_firerockets, *s_sg_firelighting, *s_sg_fire;

	s_sg_firebullets = ( tg_data.sg_fire_bullets ) ?
	    _M2 LED_B "Fire bullets ON            \n" : 
        _M2 LED_R "Fire bullets OFF           \n";
	s_sg_firerockets = ( tg_data.sg_fire_rockets ) ?
	    _M3 LED_B "Fire rockets ON            \n" : 
        _M3 LED_R "Fire rockets OFF           \n";
	s_sg_firelighting = ( tg_data.sg_fire_lighting ) ?
	    _M4 LED_B "Fire lighting ON           \n" : 
        _M4 LED_R "Fire lighting OFF          \n";

	if ( !tg_data.sg_disable_fire )
		s_sg_fire = _M1 LED_B "fire ON                    \n";
	else
		s_sg_fire = _M1 LED_R "fire OFF                   \n";

	CenterPrint( self, "Sentry Gun Fire type:\n"
		           "%s%s%s%s" 
		           _M5 " Nothing                    \n", 
		           s_sg_fire,s_sg_firebullets, s_sg_firerockets, s_sg_firelighting);

}
void TG_SG_Fire_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		tg_data.sg_disable_fire = ( tg_data.sg_disable_fire ) ? 0 : 1;
		break;
	case 2:
		tg_data.sg_fire_bullets = ( tg_data.sg_fire_bullets ) ? false : true;
		break;
	case 3:
		tg_data.sg_fire_rockets = ( tg_data.sg_fire_rockets ) ? false : true;
		break;
	case 4:
		tg_data.sg_fire_lighting = ( tg_data.sg_fire_lighting ) ? false : true;
		break;
	case 5:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;
}

void TG_Detpack_Menu( menunum_t menu )
{
	char   *s_clip, *s_disarm, *s_drop, *s_block;

	switch ( tg_data.detpack_clip )
	{
	case TG_DETPACK_SOLID_ALL:
		s_clip = _M1 LED_B "detpack clip is ALL        \n";
		break;

	case TG_DETPACK_CLIP_ALL:
		s_clip = _M1 LED_R "detpack clip is OFF        \n";
		break;

	case TG_DETPACK_CLIP_OWNER:
	default:
		s_clip = _M1 LED_Y "detpack clip is ON         \n";
		break;
	}
	if ( tg_data.disable_disarm )
		s_disarm = _M2 LED_R "don't disarm detpacks      \n";
	else
		s_disarm = _M2 LED_B "disarm detpacks            \n";

	if ( tg_data.detpack_drop )
		s_drop = _M3 LED_B "drop detpacks              \n";
	else
		s_drop = _M3 LED_R "don't drop detpacks        \n";

	if ( tfset(detpack_block) )
		s_block = _M4 LED_R "Stack detpacks: TF2003     \n";
	else
		s_block = _M4 LED_B "Stack detpacks: TF 2.8.1   \n";

	CenterPrint( self, "Detpack options:\n"
		     "%s%s%s%s"
		     _M5 " Nothing                    \n",
		     s_clip, s_disarm, s_drop, s_block );
}

void    Detpack_SetClip(  );
void TG_Detpack_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		if ( ++( tg_data.detpack_clip ) >= TG_DETPACK_CLIP_NUM )
			tg_data.detpack_clip = 0;
		Detpack_SetClip(  );
		break;
	case 2:
		tg_data.disable_disarm = ( tg_data.disable_disarm ) ? 0 : 1;
		break;
	case 3:
		tg_data.detpack_drop = ( tg_data.detpack_drop ) ? 0 : 1;
		break;
	case 4:
        tfset_flagtoggle( detpack_block );
		break;
	case 5:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;
}

void TG_Cheats_Menu( menunum_t menu )
{
	char   *s_gren_effect, *s_gren_time;

	switch ( tg_data.gren_effect )
	{
	case TG_GREN_EFFECT_OFF:
		s_gren_effect = _M3 LED_R "Grenade effect OFF         \n";
		break;

	case TG_GREN_EFFECT_OFF_FORSELF:
		s_gren_effect = _M3 LED_Y "Grenade effect OFF for self\n";
		break;

	case TG_GREN_EFFECT_ON:
	default:
		s_gren_effect = _M3 LED_B "Grenade effect ON          \n";
		break;

	}
	switch ( tg_data.gren_time )
	{

	case 0:
	default:
		s_gren_time = _M4 LED_B "Grenade effect time: full  \n";
		break;
	case 5:
		s_gren_time = _M4 LED_R "Grenade effect time: 5 sec \n";
		break;
	case 10:
		s_gren_time = _M4 LED_Y "Grenade effect time: 10 sec\n";
		break;

	}
	CenterPrint( self, "Cheats menu:\n"
		     "%s%s%s%s%s%s"
		     _M7 " Nothing                    \n",
		     ( tg_data.
		       unlimit_ammo ) ? _M1 LED_B "Unlimited ammo ON          \n" :
		     _M1 LED_R "Unlimited ammo OFF         \n",
		     ( tg_data.
		       unlimit_grens ) ? _M2 LED_B "Unlimited grenades ON      \n" :
		     _M2 LED_R "Unlimited grenades OFF     \n", s_gren_effect, s_gren_time,
		     ( tg_data.
		       godmode ) ? _M5 LED_B "God Mode ON                \n" :
		     _M5 LED_R "God Mode OFF               \n",
		     ( tg_data.
		       disable_reload ) ? _M6 LED_B "Reload Disabled            \n" :
		     _M6 LED_R "Reload Enabled             \n" );
}

void TG_Cheats_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		tg_data.unlimit_ammo = ( tg_data.unlimit_ammo ) ? 0 : 1;
		break;
	case 2:
		tg_data.unlimit_grens = ( tg_data.unlimit_grens ) ? 0 : 1;
		break;
	case 3:
		if ( ++( tg_data.gren_effect ) >= TG_GREN_EFFECT_NUM )
			tg_data.gren_effect = 0;
		break;
	case 4:
		tg_data.gren_time += 5;
		if ( tg_data.gren_time > 10 )
			tg_data.gren_time = 0;
		break;
	case 5:
		tg_data.godmode = ( tg_data.godmode ) ? 0 : 1;
		break;
	case 6:
		tg_data.disable_reload = ( tg_data.disable_reload ) ? 0 : 1;
		break;
	case 7:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;

}

vec3_t  savepos = { 0, 0, 0 }
,       saveangle, savevel;
void TG_SavePosition_Menu( menunum_t menu )
{
	if ( VectorCompareF( savepos, 0, 0, 0 ) )
		CenterPrint( self, "\n" _M1 " Save Position              \n"
			     "                              \n"
			     "                              \n"
			     "                              \n"
			     _M5 " Nothing                    " );
	else
		CenterPrint( self, "\n" _M1 " Save Position              \n"
			     _M2 " Show Position              \n"
			     _M3 " Restore Position           \n"
			     _M4 " Delete saved position      \n"
			     _M5 " Nothing                    " );
}


void TG_SavePosition_Menu_Input( int inp )
{
	switch ( inp )
	{
	case 1:
		VectorCopy( self->s.v.origin, savepos );
		VectorCopy( self->s.v.angles, saveangle );
		VectorCopy( self->s.v.velocity, savevel );
        TempEffectCoord( savepos, TE_TAREXPLOSION );
		ResetMenu(  );
		break;
	case 2:
		if ( VectorCompareF( savepos, 0, 0, 0 ) )
			break;
        TempEffectCoord( savepos, TE_TAREXPLOSION );
		G_sprint( self, 2, "Saved position: '%.0f %.0f %.0f'\n", savepos[0],
			  savepos[1], savepos[2] );
		G_sprint( self, 2, "angle: '%.0f %.0f %.0f'\n", saveangle[0],
			  saveangle[1], saveangle[2] );
		G_sprint( self, 2, "speed: '%.0f %.0f %.0f'\n", savevel[0], savevel[1],
			  savevel[2] );
		break;
	case 3:
		VectorCopy( savepos, self->s.v.origin );
		VectorCopy( saveangle, self->s.v.angles );
		VectorCopy( savevel, self->s.v.velocity );
		setorigin( self, PASSVEC3( savepos ) );
		self->s.v.fixangle = 1;
		ResetMenu(  );
		break;
	case 4:
		SetVector( savepos, 0, 0, 0 );
		ResetMenu(  );
		break;
	case 5:
		ResetMenu(  );
		self->s.v.impulse = 0;
		break;
	default:
		return;
	}

	self->s.v.impulse = 0;
	self->menu_count = 23;

}
