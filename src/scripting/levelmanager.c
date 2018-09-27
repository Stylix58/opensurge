/*
 * Open Surge Engine
 * levelmanager.c - scripting system: LevelManager object
 * Copyright (C) 2018  Alexandre Martins <alemartf(at)gmail(dot)com>
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

#include <surgescript.h>
#include "../core/util.h"
#include "../scenes/level.h"

/* private */
static surgescript_var_t* fun_constructor(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_main(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_spawn(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_destroy(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_onlevelload(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_onlevelunload(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static surgescript_var_t* fun_getcurrentlevel(surgescript_object_t* object, const surgescript_var_t** param, int num_params);
static const surgescript_heapptr_t LEVEL_ADDR = 0; /* address of the "Level" instance */

/*
 * scripting_register_levelmanager()
 * Register the LevelManager object
 */
void scripting_register_levelmanager(surgescript_vm_t* vm)
{
    surgescript_vm_bind(vm, "LevelManager", "state:main", fun_main, 0);
    surgescript_vm_bind(vm, "LevelManager", "constructor", fun_constructor, 0);
    surgescript_vm_bind(vm, "LevelManager", "spawn", fun_spawn, 1);
    surgescript_vm_bind(vm, "LevelManager", "destroy", fun_destroy, 0);
    surgescript_vm_bind(vm, "LevelManager", "onLevelLoad", fun_onlevelload, 0);
    surgescript_vm_bind(vm, "LevelManager", "onLevelUnload", fun_onlevelunload, 0);
    surgescript_vm_bind(vm, "LevelManager", "get_currentLevel", fun_getcurrentlevel, 0);
}

/* constructor */
surgescript_var_t* fun_constructor(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* allocate space for storing a reference to the Level object */
    surgescript_heap_t* heap = surgescript_object_heap(object);
    ssassert(LEVEL_ADDR == surgescript_heap_malloc(heap));
    return NULL;
}

/* main state */
surgescript_var_t* fun_main(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* do nothing */
    return NULL;
}

/* spawn function */
surgescript_var_t* fun_spawn(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* disabled */
    return NULL;
}

/* destroy function */
surgescript_var_t* fun_destroy(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* disabled */
    return NULL;
}

/* called when a level is loaded */
surgescript_var_t* fun_onlevelload(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* spawn an instance of "Level" */
    surgescript_heap_t* heap = surgescript_object_heap(object);
    surgescript_objectmanager_t* manager = surgescript_object_manager(object);
    surgescript_objecthandle_t me = surgescript_object_handle(object);
    surgescript_objecthandle_t child = surgescript_objectmanager_spawn(manager, me, "Level", NULL);
    surgescript_var_set_objecthandle(surgescript_heap_at(heap, LEVEL_ADDR), child);
    return NULL;
}

/* called when a level is unloaded */
surgescript_var_t* fun_onlevelunload(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    /* destroy the "Level" instance */
    surgescript_heap_t* heap = surgescript_object_heap(object);
    surgescript_objectmanager_t* manager = surgescript_object_manager(object);
    surgescript_objecthandle_t child = surgescript_var_get_objecthandle(surgescript_heap_at(heap, LEVEL_ADDR));
    surgescript_object_t* level = surgescript_objectmanager_get(manager, child);
    surgescript_object_kill(level); /* destroy the Level, as well as its objects */
    surgescript_var_set_null(surgescript_heap_at(heap, LEVEL_ADDR)); /* nobody can access the Level now */
    return NULL;
}

/* get the "Level" instance */
surgescript_var_t* fun_getcurrentlevel(surgescript_object_t* object, const surgescript_var_t** param, int num_params)
{
    surgescript_heap_t* heap = surgescript_object_heap(object);
    return surgescript_var_clone(surgescript_heap_at(heap, LEVEL_ADDR));
}