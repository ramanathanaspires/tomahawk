/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#ifndef TRACKPROXYMODEL_H
#define TRACKPROXYMODEL_H

#include <QtGui/QSortFilterProxyModel>

#include "PlaylistInterface.h"
#include "playlist/PlayableModel.h"

#include "DllMacro.h"

class DLLEXPORT PlayableProxyModel : public QSortFilterProxyModel
{
Q_OBJECT

public:
    explicit PlayableProxyModel ( QObject* parent = 0 );
    virtual ~PlayableProxyModel() {}

    virtual PlayableModel* sourceModel() const { return m_model; }
    virtual void setSourcePlayableModel( PlayableModel* sourceModel );
    virtual void setSourceModel( QAbstractItemModel* model );

    virtual bool isLoading() const;

    virtual QPersistentModelIndex currentIndex() const { return mapFromSource( m_model->currentItem() ); }
    virtual void setCurrentIndex( const QModelIndex& index ) { m_model->setCurrentItem( mapToSource( index ) ); }

    virtual void removeIndex( const QModelIndex& index );
    virtual void removeIndexes( const QModelIndexList& indexes );
    virtual void removeIndexes( const QList< QPersistentModelIndex >& indexes );

    virtual bool showOfflineResults() const { return m_showOfflineResults; }
    virtual void setShowOfflineResults( bool b );

    virtual bool hideDupeItems() const { return m_hideDupeItems; }
    virtual void setHideDupeItems( bool b );

    virtual int maxVisibleItems() const { return m_maxVisibleItems; }
    virtual void setMaxVisibleItems( int items );

    virtual void emitFilterChanged( const QString &pattern ) { emit filterChanged( pattern ); }

    virtual PlayableItem* itemFromIndex( const QModelIndex& index ) const { return sourceModel()->itemFromIndex( index ); }

    virtual Tomahawk::playlistinterface_ptr playlistInterface();

signals:
    void filterChanged( const QString& filter );

    void filteringStarted();
    void filteringFinished();

    void loadingStarted();
    void loadingFinished();

protected:
    virtual bool filterAcceptsRow( int sourceRow, const QModelIndex& sourceParent ) const;
    virtual bool lessThan( const QModelIndex& left, const QModelIndex& right ) const;

    Tomahawk::playlistinterface_ptr m_playlistInterface;

private:
    virtual bool lessThan( int column, const Tomahawk::query_ptr& left, const Tomahawk::query_ptr& right ) const;

    PlayableModel* m_model;

    bool m_showOfflineResults;
    bool m_hideDupeItems;
    int m_maxVisibleItems;
};

#endif // TRACKPROXYMODEL_H
