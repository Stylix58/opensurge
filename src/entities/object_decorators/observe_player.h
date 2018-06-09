/*
 * Open Surge Engine
 * observe_player.h - Observes a player
 * Copyright (C) 2010  Alexandre Martins <alemartf(at)gmail(dot)com>
 * http://opensurge2d.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _OD_OBSERVEPLAYER_H
#define _OD_OBSERVEPLAYER_H

#include "base/objectdecorator.h"

objectmachine_t* objectdecorator_observeplayer_new(objectmachine_t *decorated_machine, const char *player_name);
objectmachine_t* objectdecorator_observecurrentplayer_new(objectmachine_t *decorated_machine);
objectmachine_t* objectdecorator_observeactiveplayer_new(objectmachine_t *decorated_machine);
objectmachine_t* objectdecorator_observeallplayers_new(objectmachine_t *decorated_machine);

#endif

