/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "databasecommand_allartists.h"

#include <QSqlQuery>

#include "databaseimpl.h"
#include "utils/logger.h"


void
DatabaseCommand_AllArtists::exec( DatabaseImpl* dbi )
{
    TomahawkSqlQuery query = dbi->newquery();
    QList<Tomahawk::artist_ptr> al;
    QString orderToken, sourceToken, filterToken, tables;

    switch ( m_sortOrder )
    {
        case 0:
            break;

        case ModificationTime:
            orderToken = "file.mtime";
    }

    if ( !m_collection.isNull() )
        sourceToken = QString( "AND file.source %1" ).arg( m_collection->source()->isLocal() ? "IS NULL" : QString( "= %1" ).arg( m_collection->source()->id() ) );

    if ( !m_filter.isEmpty() )
    {
        filterToken = QString( "AND file_join.track = track.id AND ( artist.name LIKE :filterA OR track.name LIKE :filterT )" );
        tables = "artist, track, file, file_join";
    }
    else
        tables = "artist, file, file_join";

    QString sql = QString(
            "SELECT DISTINCT artist.id, artist.name "
            "FROM %1 "
            "WHERE file.id = file_join.file "
            "AND file_join.artist = artist.id "
            "%2 %3 %4 %5 %6"
            ).arg( tables )
             .arg( sourceToken )
             .arg( filterToken )
             .arg( m_sortOrder > 0 ? QString( "ORDER BY %1" ).arg( orderToken ) : QString() )
             .arg( m_sortDescending ? "DESC" : QString() )
             .arg( m_amount > 0 ? QString( "LIMIT 0, %1" ).arg( m_amount ) : QString() );

    query.prepare( sql );
    if ( !m_filter.isEmpty() )
    {
        query.bindValue( ":filterA", QString( "%%1%" ).arg( m_filter ) );
        query.bindValue( ":filterT", QString( "%%1%" ).arg( m_filter ) );
    }

    query.exec();

    while( query.next() )
    {
        Tomahawk::artist_ptr artist = Tomahawk::Artist::get( query.value( 0 ).toUInt(), query.value( 1 ).toString() );

        al << artist;
    }

    if ( al.count() )
        emit artists( al );
    emit done();
}
