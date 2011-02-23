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


#ifndef ITEM_DESCRIPTION_H
#define ITEM_DESCRIPTION_H

#include "interfaces.h"
#include "database.h"

class ItemDescription : public QObject, ModeInterface {
    Q_OBJECT
    Q_INTERFACES(ModeInterface)
private:
    void change_type(int type);
    QWiget *_cache_info;
    QWiget *_waypoint_info;
    QWiget *_track_info;
    QWiget *_route_info;
};

#endif 
