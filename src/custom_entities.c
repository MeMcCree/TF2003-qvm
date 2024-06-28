#include "g_local.h"

void func_rotatable_think() {
	self->s.v.angles[1] = anglemod(anglemod(self->s.v.angles[1]) + self->s.v.yaw_speed);
}

void SP_func_rotatable() {
	if (!CheckExistence()) {
		dremove(self);
		return;
	}

	self->s.v.movetype = MOVETYPE_NONE;
	self->s.v.solid = SOLID_BSP;
	self->s.v.yaw_speed = self->s.v.angles;
	setmodel(self, self->s.v.model);

	self->s.v.think = (func_t)func_rotatable_think;
}