#include "g_local.h"

void    tfgoalitem_RemoveFromPlayer( gedict_t * Item, gedict_t * AP, int method );
void    TeamFortress_SpyCalcName( gedict_t * spy );
void    TeamFortress_SpyUndercoverThink(  );
void    GasGrenadeMakeGas(  );
void    T_TranqDartTouch(  );
void    HallucinationTimer(  );
void    TranquiliserTimer(  );
void    spawn_touchblood( float damage );

void spy_diea1(  )
{
	self->s.v.frame = 50;
	self->s.v.think = ( func_t ) spy_diea2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea2(  )
{
	self->s.v.frame = 51;
	self->s.v.think = ( func_t ) spy_diea3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea3(  )
{
	self->s.v.frame = 52;
	self->s.v.think = ( func_t ) spy_diea4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea4(  )
{
	self->s.v.frame = 53;
	self->s.v.think = ( func_t ) spy_diea5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea5(  )
{
	self->s.v.frame = 54;
	self->s.v.think = ( func_t ) spy_diea6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea6(  )
{
	self->s.v.frame = 55;
	self->s.v.think = ( func_t ) spy_diea7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea7(  )
{
	self->s.v.frame = 56;
	self->s.v.think = ( func_t ) spy_diea8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea8(  )
{
	self->s.v.frame = 57;
	self->s.v.think = ( func_t ) spy_diea9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea9(  )
{
	self->s.v.frame = 58;
	self->s.v.think = ( func_t ) spy_diea10;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea10(  )
{
	self->s.v.frame = 59;
	self->s.v.think = ( func_t ) spy_diea11;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diea11(  )
{
	self->s.v.frame = 60;
	self->s.v.think = ( func_t ) spy_diea11;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb1(  )
{
	self->s.v.frame = 61;
	self->s.v.think = ( func_t ) spy_dieb2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb2(  )
{
	self->s.v.frame = 62;
	self->s.v.think = ( func_t ) spy_dieb3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb3(  )
{
	self->s.v.frame = 63;
	self->s.v.think = ( func_t ) spy_dieb4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb4(  )
{
	self->s.v.frame = 64;
	self->s.v.think = ( func_t ) spy_dieb5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb5(  )
{
	self->s.v.frame = 65;
	self->s.v.think = ( func_t ) spy_dieb6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb6(  )
{
	self->s.v.frame = 66;
	self->s.v.think = ( func_t ) spy_dieb7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb7(  )
{
	self->s.v.frame = 67;
	self->s.v.think = ( func_t ) spy_dieb8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb8(  )
{
	self->s.v.frame = 68;
	self->s.v.think = ( func_t ) spy_dieb9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_dieb9(  )
{
	self->s.v.frame = 69;
	self->s.v.think = ( func_t ) spy_dieb9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec1(  )
{
	self->s.v.frame = 70;
	self->s.v.think = ( func_t ) spy_diec2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec2(  )
{
	self->s.v.frame = 71;
	self->s.v.think = ( func_t ) spy_diec3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec3(  )
{
	self->s.v.frame = 72;
	self->s.v.think = ( func_t ) spy_diec4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec4(  )
{
	self->s.v.frame = 73;
	self->s.v.think = ( func_t ) spy_diec5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec5(  )
{
	self->s.v.frame = 74;
	self->s.v.think = ( func_t ) spy_diec6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec6(  )
{
	self->s.v.frame = 75;
	self->s.v.think = ( func_t ) spy_diec7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec7(  )
{
	self->s.v.frame = 76;
	self->s.v.think = ( func_t ) spy_diec8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec8(  )
{
	self->s.v.frame = 77;
	self->s.v.think = ( func_t ) spy_diec9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec9(  )
{
	self->s.v.frame = 78;
	self->s.v.think = ( func_t ) spy_diec10;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec10(  )
{
	self->s.v.frame = 79;
	self->s.v.think = ( func_t ) spy_diec11;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec11(  )
{
	self->s.v.frame = 80;
	self->s.v.think = ( func_t ) spy_diec12;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec12(  )
{
	self->s.v.frame = 81;
	self->s.v.think = ( func_t ) spy_diec13;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec13(  )
{
	self->s.v.frame = 82;
	self->s.v.think = ( func_t ) spy_diec14;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec14(  )
{
	self->s.v.frame = 83;
	self->s.v.think = ( func_t ) spy_diec15;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diec15(  )
{
	self->s.v.frame = 84;
	self->s.v.think = ( func_t ) spy_diec15;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died1(  )
{
	self->s.v.frame = 85;
	self->s.v.think = ( func_t ) spy_died2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died2(  )
{
	self->s.v.frame = 86;
	self->s.v.think = ( func_t ) spy_died3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died3(  )
{
	self->s.v.frame = 87;
	self->s.v.think = ( func_t ) spy_died4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died4(  )
{
	self->s.v.frame = 88;
	self->s.v.think = ( func_t ) spy_died5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died5(  )
{
	self->s.v.frame = 89;
	self->s.v.think = ( func_t ) spy_died6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died6(  )
{
	self->s.v.frame = 90;
	self->s.v.think = ( func_t ) spy_died7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died7(  )
{
	self->s.v.frame = 91;
	self->s.v.think = ( func_t ) spy_died8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died8(  )
{
	self->s.v.frame = 92;
	self->s.v.think = ( func_t ) spy_died9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_died9(  )
{
	self->s.v.frame = 93;
	self->s.v.think = ( func_t ) spy_died9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee1(  )
{
	self->s.v.frame = 94;
	self->s.v.think = ( func_t ) spy_diee2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee2(  )
{
	self->s.v.frame = 95;
	self->s.v.think = ( func_t ) spy_diee3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee3(  )
{
	self->s.v.frame = 96;
	self->s.v.think = ( func_t ) spy_diee4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee4(  )
{
	self->s.v.frame = 97;
	self->s.v.think = ( func_t ) spy_diee5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee5(  )
{
	self->s.v.frame = 98;
	self->s.v.think = ( func_t ) spy_diee6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee6(  )
{
	self->s.v.frame = 99;
	self->s.v.think = ( func_t ) spy_diee7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee7(  )
{
	self->s.v.frame = 100;
	self->s.v.think = ( func_t ) spy_diee8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee8(  )
{
	self->s.v.frame = 101;
	self->s.v.think = ( func_t ) spy_diee9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_diee9(  )
{
	self->s.v.frame = 102;
	self->s.v.think = ( func_t ) spy_diee9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax1(  )
{
	self->s.v.frame = 41;
	self->s.v.think = ( func_t ) spy_die_ax2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax2(  )
{
	self->s.v.frame = 42;
	self->s.v.think = ( func_t ) spy_die_ax3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax3(  )
{
	self->s.v.frame = 43;
	self->s.v.think = ( func_t ) spy_die_ax4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax4(  )
{
	self->s.v.frame = 44;
	self->s.v.think = ( func_t ) spy_die_ax5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax5(  )
{
	self->s.v.frame = 45;
	self->s.v.think = ( func_t ) spy_die_ax6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax6(  )
{
	self->s.v.frame = 46;
	self->s.v.think = ( func_t ) spy_die_ax7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax7(  )
{
	self->s.v.frame = 47;
	self->s.v.think = ( func_t ) spy_die_ax8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax8(  )
{
	self->s.v.frame = 48;
	self->s.v.think = ( func_t ) spy_die_ax9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_die_ax9(  )
{
	self->s.v.frame = 49;
	self->s.v.think = ( func_t ) spy_die_ax9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb1(  )
{
	self->s.v.frame = 69;
	self->s.v.think = ( func_t ) spy_upb2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb2(  )
{
	self->s.v.frame = 68;
	self->s.v.think = ( func_t ) spy_upb3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb3(  )
{
	self->s.v.frame = 67;
	self->s.v.think = ( func_t ) spy_upb4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb4(  )
{
	self->s.v.frame = 66;
	self->s.v.think = ( func_t ) spy_upb5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb5(  )
{
	self->s.v.frame = 65;
	self->s.v.think = ( func_t ) spy_upb6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb6(  )
{
	self->s.v.frame = 64;
	self->s.v.think = ( func_t ) spy_upb7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb7(  )
{
	self->s.v.frame = 63;
	self->s.v.think = ( func_t ) spy_upb8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb8(  )
{
	self->s.v.frame = 62;
	self->s.v.think = ( func_t ) spy_upb9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upb9(  )
{
	self->s.v.frame = 61;
	self->s.v.think = ( func_t ) spy_upb9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

	player_stand1(  );
};
void spy_upc1(  )
{
	self->s.v.frame = 84;
	self->s.v.think = ( func_t ) spy_upc2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc2(  )
{
	self->s.v.frame = 83;
	self->s.v.think = ( func_t ) spy_upc3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc3(  )
{
	self->s.v.frame = 82;
	self->s.v.think = ( func_t ) spy_upc4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc4(  )
{
	self->s.v.frame = 81;
	self->s.v.think = ( func_t ) spy_upc5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc5(  )
{
	self->s.v.frame = 80;
	self->s.v.think = ( func_t ) spy_upc6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc6(  )
{
	self->s.v.frame = 79;
	self->s.v.think = ( func_t ) spy_upc7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc7(  )
{
	self->s.v.frame = 78;
	self->s.v.think = ( func_t ) spy_upc8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc8(  )
{
	self->s.v.frame = 77;
	self->s.v.think = ( func_t ) spy_upc9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc9(  )
{
	self->s.v.frame = 76;
	self->s.v.think = ( func_t ) spy_upc10;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc10(  )
{
	self->s.v.frame = 75;
	self->s.v.think = ( func_t ) spy_upc11;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc11(  )
{
	self->s.v.frame = 74;
	self->s.v.think = ( func_t ) spy_upc12;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc12(  )
{
	self->s.v.frame = 73;
	self->s.v.think = ( func_t ) spy_upc13;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc13(  )
{
	self->s.v.frame = 72;
	self->s.v.think = ( func_t ) spy_upc14;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc14(  )
{
	self->s.v.frame = 71;
	self->s.v.think = ( func_t ) spy_upc15;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upc15(  )
{
	self->s.v.frame = 70;
	self->s.v.think = ( func_t ) spy_upc15;
	self->s.v.nextthink = g_globalvars.time + 0.1;

	player_stand1(  );
};
void spy_upd1(  )
{
	self->s.v.frame = 93;
	self->s.v.think = ( func_t ) spy_upd2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd2(  )
{
	self->s.v.frame = 92;
	self->s.v.think = ( func_t ) spy_upd3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd3(  )
{
	self->s.v.frame = 91;
	self->s.v.think = ( func_t ) spy_upd4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd4(  )
{
	self->s.v.frame = 90;
	self->s.v.think = ( func_t ) spy_upd5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd5(  )
{
	self->s.v.frame = 89;
	self->s.v.think = ( func_t ) spy_upd6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd6(  )
{
	self->s.v.frame = 88;
	self->s.v.think = ( func_t ) spy_upd7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd7(  )
{
	self->s.v.frame = 87;
	self->s.v.think = ( func_t ) spy_upd8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd8(  )
{
	self->s.v.frame = 86;
	self->s.v.think = ( func_t ) spy_upd9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upd9(  )
{
	self->s.v.frame = 85;
	self->s.v.think = ( func_t ) spy_upd9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

	player_stand1(  );
};
void spy_upe1(  )
{
	self->s.v.frame = 94;
	self->s.v.think = ( func_t ) spy_upe9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};


void    spy_upe9(  );
void spy_upe2(  )
{
	self->s.v.frame = 95;
	self->s.v.think = ( func_t ) spy_upe8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};


void    spy_upe8(  );
void spy_upe3(  )
{
	self->s.v.frame = 96;
	self->s.v.think = ( func_t ) spy_upe7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};


void    spy_upe7(  );
void spy_upe4(  )
{
	self->s.v.frame = 97;
	self->s.v.think = ( func_t ) spy_upe6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};


void    spy_upe6(  );
void spy_upe5(  )
{
	self->s.v.frame = 98;
	self->s.v.think = ( func_t ) spy_upe5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upe6(  )
{
	self->s.v.frame = 99;
	self->s.v.think = ( func_t ) spy_upe4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upe7(  )
{
	self->s.v.frame = 100;
	self->s.v.think = ( func_t ) spy_upe3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upe8(  )
{
	self->s.v.frame = 101;
	self->s.v.think = ( func_t ) spy_upe2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upe9(  )
{
	self->s.v.frame = 102;
	self->s.v.think = ( func_t ) spy_upe1;
	self->s.v.nextthink = g_globalvars.time + 0.1;

	player_stand1(  );
};
void spy_upaxe1(  )
{
	self->s.v.frame = 49;
	self->s.v.think = ( func_t ) spy_upaxe2;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe2(  )
{
	self->s.v.frame = 48;
	self->s.v.think = ( func_t ) spy_upaxe3;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe3(  )
{
	self->s.v.frame = 47;
	self->s.v.think = ( func_t ) spy_upaxe4;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe4(  )
{
	self->s.v.frame = 46;
	self->s.v.think = ( func_t ) spy_upaxe5;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe5(  )
{
	self->s.v.frame = 45;
	self->s.v.think = ( func_t ) spy_upaxe6;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe6(  )
{
	self->s.v.frame = 44;
	self->s.v.think = ( func_t ) spy_upaxe7;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe7(  )
{
	self->s.v.frame = 43;
	self->s.v.think = ( func_t ) spy_upaxe8;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe8(  )
{
	self->s.v.frame = 42;
	self->s.v.think = ( func_t ) spy_upaxe9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

};
void spy_upaxe9(  )
{
	self->s.v.frame = 41;
	self->s.v.think = ( func_t ) spy_upaxe9;
	self->s.v.nextthink = g_globalvars.time + 0.1;

	player_stand1(  );
};

void TeamFortress_SpyFeignDeath( int issilent )
{
	int     i, j;
	gedict_t *at_spot;
	gedict_t *te;

	self->StatusRefreshTime = g_globalvars.time + 0.1;
	if ( self->is_feigning )
	{
		at_spot = findradius( world, self->s.v.origin, 64 );
		i = 1;
		j = 0;
		while ( at_spot )
		{
			if ( streq( at_spot->mdl, "progs/detpack.mdl" ) )
				j = 1;
			if ( streq( at_spot->mdl, "progs/detpack2.mdl" ) && tf_data.birthday == 1 )
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
			at_spot = findradius( at_spot, self->s.v.origin, 64 );
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
		if ( self->s.v.weapon <= 16 )
		{
			spy_upaxe1(  );
			return;
		}
		switch ( ( int ) ( g_random(  ) * 4 ) )
		{
		case 0:
			spy_upb1(  );
			break;
		case 1:
			spy_upc1(  );
			break;
		case 2:
			spy_upd1(  );
			break;
		default:
			spy_upe1(  );
			break;
		}
		return;
	} else
	{
		// !self->is_feigning
		if ( self->hook_out )
		{
			G_sprint( self, 2, "You can't feign with the hook out.\n" );
			return;
		}
/*          if (self.is_unabletospy == 1) {
           G_sprint(self, 2, "You can't go undercover right now.\n");
           return;
          }*/

/*  if (!(self.flags & 512) && !self->s.v.waterlevel) {
   G_sprint(self, 2, "You can't feign in the air.\n");
   return;
  }*/
		at_spot = world;
		while ( at_spot = findradius( at_spot, self->s.v.origin, 64 ) )
		{
			if ( streq( at_spot->s.v.classname, "player" ) && self != at_spot && at_spot->is_feigning == 1 )
			{
				G_sprint( self, 2, "You can't feign on top of another spy!\n" );
				return;
			}
		}
//  self.immune_to_check = g_globalvars.time + 5;
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
		if ( self->s.v.weapon <= 16 )
		{
			spy_die_ax1(  );
			return;
		}
		te = world;
		while ( te = find( te, FOFS( s.v.classname ), "item_tfgoal" ) )
		{
			if ( te->s.v.owner != EDICT_TO_PROG( self ) )
				continue;

			if ( !( te->goal_activation & TFGI_KEEP ) || self->has_disconnected == 1 )
				tfgoalitem_RemoveFromPlayer( te, self, 0 );
			if ( CTF_Map == 1 )
			{
				if ( te->goal_no == 1 )
					G_bprint( 2, "%s ���� the ���� flag!\n", self->s.v.netname );
				else
					G_bprint( 2, "%s ���� the ��� flag!\n", self->s.v.netname );
			}
		}
		switch ( ( int ) ( g_random(  ) * 5 ) )
		{
		case 0:
			spy_diea1(  );
			break;
		case 1:
			spy_dieb1(  );
			break;
		case 2:
			spy_diec1(  );
			break;
		case 3:
			spy_died1(  );
			break;
		default:
			spy_diee1(  );
			break;
		}
	}
}

void TeamFortress_SpyGoUndercover(  )
{
	gedict_t *te;


	if ( tf_data.invis_only == 1 )
	{

		if ( ( int ) self->s.v.effects & ( 8 | 4 ) )
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
			self->s.v.modelindex = modelindex_player;
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
			self->is_undercover = 0;
		}
	}
}

void TeamFortress_SpyCalcName( gedict_t * spy )
{
	gedict_t *te;

	spy->undercover_name = NULL;
	if ( spy->undercover_team )
	{
		for ( te = world; te = find( te, FOFS( s.v.classname ), "player" ); )
		{
			if ( te->team_no == spy->undercover_team && te->s.v.skin == spy->undercover_skin )
			{
				spy->undercover_name = te->s.v.netname;
				break;
			}
		}
		if ( !spy->undercover_name )
		{

			for ( te = world; te = find( te, FOFS( s.v.classname ), "player" ); )
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

void TeamFortress_SpyUndercoverThink(  )
{
	gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

	if ( owner->playerclass != PC_SPY )
		return;
	if ( owner->is_undercover == 2 )
	{
		if ( tf_data.invis_only == 1 )
		{
			owner->s.v.items = ( int ) owner->s.v.items | IT_INVISIBILITY;
			owner->s.v.frame = 0;
			owner->s.v.modelindex = modelindex_eyes;
			owner->is_undercover = 1;
		} else
		{
			owner->immune_to_check = g_globalvars.time + tf_data.cheat_pause;	//10;
			if ( self->s.v.skin )
			{
				G_sprint( owner, 2, "Skin set to " );
				TeamFortress_PrintClassName( owner, self->s.v.skin, 0 );
				owner->undercover_skin = self->s.v.skin;
				TeamFortress_SetSkin( owner );
			}
			if ( self->s.v.team )
			{
				G_sprint( owner, 2, "Colors set to Team %.0f\n", self->s.v.team );
				owner->undercover_team = self->s.v.team;
				stuffcmd( owner, "color %d %d\n", TeamFortress_TeamGetTopColor( self->s.v.team ),
					  TeamFortress_TeamGetColor( self->s.v.team ) - 1 );
				TeamFortress_SetSkin( owner );
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

void TeamFortress_SpyChangeSkin( int class )
{
	gedict_t *te;

	if ( class == PC_SPY )
	{

		if ( self->undercover_skin == 0 )
		{
			G_sprint( self, 2, "Skin reset.\n" );
			return;
		}
		G_sprint( self, 2, "Skin reset." );
		self->undercover_skin = 0;
		TeamFortress_SetSkin( self );
		if ( !self->undercover_team )
			self->is_undercover = 0;
		return;
	}
	G_sprint( self, 2, "Going undercover...\n" );
	self->is_undercover = 2;
	te = spawn(  );
	te->s.v.classname = "timer";
	te->s.v.owner = EDICT_TO_PROG( self );
	te->s.v.think = ( func_t ) TeamFortress_SpyUndercoverThink;
	te->s.v.nextthink = g_globalvars.time + 4;
	te->s.v.skin = class;
	TeamFortress_SetSkin( self );
}

void TeamFortress_SpyChangeColor( int teamno )
{
	gedict_t *te;

	if ( teamno == self->team_no )
	{

		if ( self->undercover_team == 0 )
		{
			G_sprint( self, 2, "Colors reset.\n" );
			return;
		}
		G_sprint( self, 2, "Colors reset.\n" );
		self->immune_to_check = g_globalvars.time + tf_data.cheat_pause;	//10;
		self->undercover_team = 0;
		stuffcmd( self, "color %d %d\n", TeamFortress_TeamGetTopColor( self->team_no ),
			  TeamFortress_TeamGetColor( self->team_no ) - 1 );

		if ( !self->undercover_skin )
			self->is_undercover = 0;
		TeamFortress_SetSkin( self );
		return;
	}
	G_sprint( self, 2, "Going undercover...\n" );
	self->is_undercover = 2;
	te = spawn(  );
	te->s.v.classname = "timer";
	te->s.v.owner = EDICT_TO_PROG( self );
	te->s.v.think = ( func_t ) TeamFortress_SpyUndercoverThink;
	te->s.v.nextthink = g_globalvars.time + 4;
	te->s.v.team = teamno;
}

void GasGrenadeTouch(  )
{
	sound( self, 1, "weapons/bounce.wav", 1, 1 );
	if ( VectorCompareF( self->s.v.velocity, 0, 0, 0 ) )
		SetVector( self->s.v.avelocity, 0, 0, 0 );
}

void GasGrenadeExplode(  )
{
	gedict_t *te;
	float   pos;

	pos = trap_pointcontents( PASSVEC3( self->s.v.origin ) );
	if ( pos == -1 )
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
		for ( pos = 0; pos < 10; pos++ )
		{
			newmis = spawn(  );
			setmodel( newmis, "progs/s_bubble.spr" );
			setorigin( newmis, PASSVEC3( self->s.v.origin ) );
			newmis->s.v.movetype = MOVETYPE_NOCLIP;
			newmis->s.v.solid = SOLID_NOT;
			SetVector( newmis->s.v.velocity, 0, 0, 15 );
			newmis->s.v.velocity[2] = 10 + g_random(  ) * 20;
			newmis->s.v.nextthink = g_globalvars.time + 0.5;
			newmis->s.v.think = ( func_t ) bubble_bob;
			newmis->s.v.classname = "bubble";
			newmis->s.v.frame = 0;
			newmis->cnt = 0;
			setsize( newmis, -8, -8, -8, 8, 8, 8 );
		}
	}
	dremove( self );
}

void GasGrenadeMakeGas(  )
{
	gedict_t *te;
	gedict_t *timer;

	self->s.v.nextthink = g_globalvars.time + 0.75;
	for ( te = world; te = findradius( te, self->s.v.origin, 200 ); )
	{
		if ( streq( te->s.v.classname, "player" ) && !te->s.v.deadflag && te->has_disconnected != 1 )
		{
			tf_data.deathmsg = DMSG_GREN_GAS;
			TF_T_Damage( te, world, PROG_TO_EDICT( self->s.v.owner ), 10, 1 | 2, 0 );
			if ( te->tfstate & TFSTATE_HALLUCINATING )
			{
				for ( timer = world; timer = find( timer, FOFS( s.v.classname ), "timer" ); )
				{
					if ( PROG_TO_EDICT( timer->s.v.owner ) != te )
						continue;
					if ( timer->s.v.think != ( func_t ) HallucinationTimer )
						continue;
				}
				if ( timer )
				{
					timer->s.v.health = timer->s.v.health + 25;
					//if ( tf_data.old_grens == 1 )
					if(!( tf_data.new_gas & GAS_MASK_NEWGREN_TIMES))
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
					    
					if( !( tf_data.new_gas & GAS_MASK_ALLSPYS ) && (g_random() < SETGAS_IN_GAS_TIME))
						SetGasSkins(te);
				}
			} else
			{
				//if ( tf_data.old_grens == 1 )
				if ( tf_data.new_gas & GAS_MASK_PALETTE)
				{
					stuffcmd( te, "v_cshift 50 25 50 -50\n" );
					G_sprint( te, 2, "Far out man!\n" );
				} else
					G_sprint( te, 2, "Run for cover! They're everywhere!\n" );
				te->tfstate = te->tfstate | TFSTATE_HALLUCINATING;
				timer = spawn(  );
				//if ( tf_data.old_grens == 1 )
				if( !(tf_data.new_gas & GAS_MASK_NEWGREN_TIMES))
					timer->s.v.nextthink = g_globalvars.time + 0.5;
				else
					timer->s.v.nextthink = g_globalvars.time + 0.3;
				timer->s.v.think = ( func_t ) HallucinationTimer;

				SetGasSkins(te);

				timer->s.v.classname = "timer";
				timer->s.v.owner = EDICT_TO_PROG( te );
				//if ( tf_data.old_grens == 1 )
				if( !(tf_data.new_gas & GAS_MASK_NEWGREN_TIMES))
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
		trap_WriteByte( 4, 23 );
		trap_WriteByte( 4, 4 );
		trap_WriteCoord( 4, self->s.v.origin[0] );
		trap_WriteCoord( 4, self->s.v.origin[1] );
		trap_WriteCoord( 4, self->s.v.origin[2] );
		trap_multicast( PASSVEC3( self->s.v.origin ), 2 );
		return;
	}
	if ( self->heat <= 20 )
	{
		self->s.v.weapon = self->s.v.weapon + 1;
		if ( self->s.v.weapon == 1 )
		{
			trap_WriteByte( 4, 23 );
			trap_WriteByte( 4, 10 );
			trap_WriteCoord( 4, self->s.v.origin[0] );
			trap_WriteCoord( 4, self->s.v.origin[1] );
			trap_WriteCoord( 4, self->s.v.origin[2] - 24 );
			trap_multicast( PASSVEC3( self->s.v.origin ), 2 );
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
	trap_WriteByte( 1, SVC_TEMPENTITY );

	switch ( ( int ) ( g_random(  ) * 3 ) )
	{
	case 0:
		trap_WriteByte( 1, 3 );
		break;
	case 1:
		trap_WriteByte( 1, 4 );
		break;
	default:
		trap_WriteByte( 1, 10 );
		break;
	}
	trap_WriteCoord( 1, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[2] );
	if( tf_data.new_gas & GAS_MASK_NEWGREN_DMG)
	//if ( tf_data.old_grens != 1 )
		T_Damage( owner, owner, owner, 0 );
}

char   *gas_sounds[] = {
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
	trap_WriteByte( 1, 23 );
	trap_WriteByte( 1, 11 );
	trap_WriteCoord( 1, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[2] );

	//if ( tf_data.old_grens == 1 )
	if ( !(tf_data.new_gas & GAS_MASK_NEWGREN_EFFECTS))
		return;
	i = g_random(  ) * ( sizeof( gas_sounds ) / sizeof( gas_sounds[0] )  );
	stuffcmd( owner, gas_sounds[i] );
}

char   *gas_sounds2[] = {
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
};
void GasEffect3( gedict_t * owner )
{
	gedict_t *te;
	int     i;

	g_globalvars.msg_entity = EDICT_TO_PROG( owner );

	te = spawn(  );
	te->s.v.origin[0] = owner->s.v.origin[0] + g_random(  ) * 800 - 400;
	te->s.v.origin[1] = owner->s.v.origin[1] + g_random(  ) * 800 - 400;
	te->s.v.origin[2] = owner->s.v.origin[2];
	trap_WriteByte( 1, SVC_TEMPENTITY );
	trap_WriteByte( 1, TE_LIGHTNING2 );
	WriteEntity( 1, te );
	trap_WriteCoord( 1, te->s.v.origin[0] );
	trap_WriteCoord( 1, te->s.v.origin[1] );
	trap_WriteCoord( 1, te->s.v.origin[2] );
	trap_WriteCoord( 1, owner->s.v.origin[0] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[1] + g_random(  ) * 800 - 400 );
	trap_WriteCoord( 1, owner->s.v.origin[2] );
	dremove( te );

	//if ( tf_data.old_grens == 1 )
	if ( !(tf_data.new_gas & GAS_MASK_NEWGREN_EFFECTS))
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

		//if ( tf_data.old_grens == 1 )
		if ( tf_data.new_gas & GAS_MASK_PALETTE) 
			stuffcmd( owner, "v_cshift; wait; bf\n" );
		G_sprint( owner, 2, "You feel a little better now.\n" );
		dremove( self );
		return;
	}
	//if ( tf_data.old_grens == 1 )
	if( !(tf_data.new_gas & GAS_MASK_NEWGREN_TIMES))
		self->s.v.nextthink = g_globalvars.time + 0.5;
	else
		self->s.v.nextthink = g_globalvars.time + 0.3;

	if(!( tf_data.new_gas & GAS_MASK_ALLSPYS ) && g_random()< SETGAS_TIMER_THINK)
		SetGasSkins(owner);
                self->s.v.nextthink = g_globalvars.time + 0.5;

	if ( g_random(  ) < 0.5 )
		KickPlayer( -10, owner );
	//if ( tf_data.old_grens == 1 )
	if ( tf_data.new_gas & GAS_MASK_PALETTE)
	{
		stuffcmd( owner, "v_cshift %d %d %d -75\n", ( int ) ( g_random(  ) * 100 ),
			  ( int ) ( g_random(  ) * 100 ), ( int ) ( g_random(  ) * 100 ) );
	}
/* tmpx = g_random() * 800 - 400;
 tmpy = g_random() * 800 - 400;
 halltype = g_random();
 halltype2 = g_random();*/
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

void W_FireTranq(  )
{

	self->s.v.currentammo = --( self->s.v.ammo_shells );

	KickPlayer( -2, self );
	newmis = spawn(  );
	newmis->s.v.owner = EDICT_TO_PROG( self );
	newmis->s.v.movetype = MOVETYPE_FLYMISSILE;
	newmis->s.v.solid = SOLID_BBOX;
	makevectors( self->s.v.v_angle );
	VectorCopy( g_globalvars.v_forward, newmis->s.v.velocity );
	VectorScale( g_globalvars.v_forward, 1500, newmis->s.v.velocity );
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
};

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
		TF_T_Damage( other, self, PROG_TO_EDICT( self->s.v.owner ), 20, 2, 2 );
		if ( streq( other->s.v.classname, "player" ) &&
		     !( other->team_no == PROG_TO_EDICT( self->s.v.owner )->team_no && ( teamplay & ( 2 | 4 ) ) ) )
		{
			if ( other->tfstate & TFSTATE_TRANQUILISED )
			{

				for ( timer = world; timer = find( timer, FOFS( s.v.classname ), "timer" ); )
				{
					if ( PROG_TO_EDICT( timer->s.v.owner ) != other )
						continue;
					if ( timer->s.v.think != ( func_t ) TranquiliserTimer )
						continue;
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
		trap_WriteByte( 4, 23 );
		if ( streq( self->s.v.classname, "wizspike" ) )
			trap_WriteByte( 4, 7 );
		else
		{
			if ( streq( self->s.v.classname, "knightspike" ) )
				trap_WriteByte( 4, 8 );
			else
				trap_WriteByte( 4, 0 );
		}
		trap_WriteCoord( 4, self->s.v.origin[0] );
		trap_WriteCoord( 4, self->s.v.origin[1] );
		trap_WriteCoord( 4, self->s.v.origin[2] );
		trap_multicast( PASSVEC3( self->s.v.origin ), 2 );
	}
	dremove( self );
}

void TranquiliserTimer(  )
{
	gedict_t *owner = PROG_TO_EDICT( self->s.v.owner );

	owner->tfstate -= owner->tfstate & TFSTATE_TRANQUILISED;
	TeamFortress_SetSpeed( owner );
	G_sprint( owner, 2, "You feel more alert now\n" );
	dremove( self );
}

void Spy_RemoveDisguise( gedict_t * spy )
{

	if ( tf_data.invis_only != 1 )
	{
		if ( spy->playerclass == PC_SPY )
		{
			if ( spy->undercover_team )
			{
				spy->immune_to_check = g_globalvars.time + tf_data.cheat_pause;	//10;
				spy->undercover_team = 0;
				stuffcmd( spy, "color %d %d\n", TeamFortress_TeamGetTopColor( spy->team_no ),
					  TeamFortress_TeamGetColor( spy->team_no ) - 1 );

			}
			if ( spy->undercover_skin )
			{
				spy->immune_to_check = g_globalvars.time + tf_data.cheat_pause;	//10;
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
			if ( ( int ) spy->s.v.items & 524288 )
			{
				spy->invisible_finished = 0;
				spy->invisible_time = 0;
				spy->s.v.items = ( int ) spy->s.v.items - 524288;
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

	if( !(tf_data.new_gas & (GAS_MASK_COLOR | GAS_MASK_SKIN | GAS_MASK_ALLSPYS)) )
		return;

	if( pl->has_disconnected )
		return;

	if( !pl->has_fake_gas_setinfo )
		return;

	for( te = world; te = find( te, FOFS( s.v.classname), "player" );)
	{
		if( te->has_disconnected )
			continue;

		entnum = NUM_FOR_EDICT(te) - 1;
		
		if( entnum > MAX_CLIENTS )
		{
			G_dprint("ResetGasSkins: entnum > MAX_CLIENTS\n");
			continue;
		}

		g_globalvars.msg_entity = EDICT_TO_PROG( pl );

		if( tf_data.new_gas & (GAS_MASK_COLOR|GAS_MASK_ALLSPYS) )
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

		if( tf_data.new_gas & (GAS_MASK_SKIN|GAS_MASK_ALLSPYS) )
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

	if( !(tf_data.new_gas & (GAS_MASK_COLOR | GAS_MASK_SKIN | GAS_MASK_ALLSPYS)) )
		return;

	if( pl->has_disconnected )
		return;

	pl->has_fake_gas_setinfo = 1;
	for( te = world; te = find( te, FOFS( s.v.classname), "player" );)
	{

		entnum = NUM_FOR_EDICT(te) - 1;
		
		if( te->has_disconnected || te == pl)
			continue;
		
		if( entnum > MAX_CLIENTS )
		{
			G_dprint("SetGasSkins: entnum > MAX_CLIENTS\n");
			continue;
		}

		g_globalvars.msg_entity = EDICT_TO_PROG( pl );
		if( tf_data.new_gas & GAS_MASK_ALLSPYS)
		{
			rteam = pl->team_no%2 + 1;

			rcol = TeamFortress_TeamGetTopColor(rteam);
			sprintf(st, "%d",rcol);
			trap_WriteByte(MSG_ONE,SVC_SETINFO );
			trap_WriteByte(MSG_ONE, entnum );
			trap_WriteString(MSG_ONE,"topcolor" );
			trap_WriteString(MSG_ONE, st);

			rcol = TeamFortress_TeamGetColor(rteam) - 1;
			sprintf(st, "%d",rcol);

			trap_WriteByte(MSG_ONE, SVC_SETINFO );
			trap_WriteByte(MSG_ONE, entnum );
			trap_WriteString(MSG_ONE,"bottomcolor" );
			trap_WriteString(MSG_ONE, st);


			GetSVInfokeyString( class_set[8].infokey4skin[rteam], NULL,
			    st, sizeof( st ), class_set[8].defaultskin );
	
			trap_WriteByte(MSG_ONE, SVC_SETINFO );
			trap_WriteByte(MSG_ONE, entnum );
			trap_WriteString(MSG_ONE,"skin" );
			trap_WriteString(MSG_ONE, st);
		}else
		{
			rteam = pl->team_no;

			if( ( tf_data.new_gas & GAS_MASK_COLOR ) && g_random()< SETGAS_SETCOLOR)
			{
				if( tf_data.new_gas & GAS_MASK_ALLCOLORS)
				{
					rcol = g_random() * 16;
				}else
				{
					if( tf_data.new_gas & GAS_MASK_4COLORS)
						rteam = g_random() * 4;
					else
						rteam = g_random() * number_of_teams;
					rteam++;
					rcol = TeamFortress_TeamGetTopColor( rteam  );
				}

				sprintf(st, "%d",rcol);
				trap_WriteByte(MSG_ONE,SVC_SETINFO );
				trap_WriteByte(MSG_ONE, entnum );
				trap_WriteString(MSG_ONE,"topcolor" );
				trap_WriteString(MSG_ONE, st);

				if( !(tf_data.new_gas & GAS_MASK_ALLCOLORS))
				{
					rcol = TeamFortress_TeamGetColor(rteam) - 1;
					sprintf(st, "%d",rcol);
				}
				trap_WriteByte(MSG_ONE,SVC_SETINFO );
				trap_WriteByte(MSG_ONE, entnum );
				trap_WriteString(MSG_ONE,"bottomcolor" );
				trap_WriteString(MSG_ONE, st);
			}

			if( (tf_data.new_gas & GAS_MASK_SKIN ) && g_random()<SETGAS_SETSKIN)
			{
				rskin = g_random() *9 +1;

				GetSVInfokeyString( class_set[rskin].infokey4skin[rteam], NULL,
						st, sizeof( st ), class_set[rskin].defaultskin );
	
				trap_WriteByte(MSG_ONE, SVC_SETINFO );
				trap_WriteByte(MSG_ONE, entnum );
				trap_WriteString(MSG_ONE,"skin" );
				trap_WriteString(MSG_ONE, st);
			}
	
		}

	}
}