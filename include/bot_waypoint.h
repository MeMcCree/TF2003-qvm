/*
 *  QWProgs-TF2003
 *  Copyright (C) 2004  [sd] angel
 *
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *  $Id: bot_waypoint.h,v 1.2 2005-06-03 04:27:52 AngelD Exp $
 */

#define MAX_WP_LINKS 20
//#define MAX_WAYPOINTS 10000

struct waypoint_s;

typedef struct wp_link_s
{
        struct waypoint_s       *src_wp,*dest_wp;
        int                     flags;
        float                   length;
        float                   req_velocity;
}wp_link_t;

typedef struct waypoint_s
{
        vec3_t                  origin;
        float                   radius;
        int                     index;
        int                     flags;
        wp_link_t*              links[MAX_WP_LINKS];
}waypoint_t;

typedef struct wp_path_s
{
        wp_link_t               *link;
        struct wp_path_s        *next;
}wp_path_t;

wp_path_t*      WaypointFindPath( vec3_t srcpoint, vec3_t destpoint );
//int             WaypointFindInRadius( vec3_t vPos, float fRadius, int* pTab, int maxcount);
waypoint_t*     WaypointFindNearestVisible(vec3_t point);
waypoint_t*     WaypointFindNearest(vec3_t point);
waypoint_t*     AddWaypoint(waypoint_t* );
qboolean        AddLink( int src_index, int dest_index, wp_link_t* newlink);
