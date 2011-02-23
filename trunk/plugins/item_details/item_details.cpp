/******************************************************************************
** Copyright 2010 Doug Penner
**
** This file is part of QGeoView.
**
** QGeoView is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QGeoView is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QGeoView.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <marble_map.h>

ItemDetails::ItemDetails()
{
    change_type(INFO_TYPE_NONE);
}

void ItemDetails::change_type(int type)
{
    _route_info->setVisible(false);
    _track_info->setVisible(false);
    _waypoint_info->setVisible(false);
    _cache_info->setVisible(false);
    switch(type) {
        case INFO_TYPE_CACHE:
            _cache_info->setVisible(true);
            break;
        case INFO_TYPE_WAYPOINT:
            _waypoint_info->setVisible(true);
            break;
        case INFO_TYPE_TRACK:
            _track_info->setVisible(true);
            break;
        case INFO_TYPE_ROUTE:
            _route_info->setVisible(true);
            break;
    }
}
