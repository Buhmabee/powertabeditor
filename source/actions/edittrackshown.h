/*
  * Copyright (C) 2012 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
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

#ifndef EDITTRACKSHOWN_H
#define EDITTRACKSHOWN_H

#include <QUndoCommand>
#include <boost/cstdint.hpp>

class Score;

class EditTrackShown : public QObject, public QUndoCommand
{
    Q_OBJECT
public:
    EditTrackShown(Score* score, uint32_t trackNumber, bool trackShown);

    void redo();
    void undo();

signals:
    void triggered();

private:
    Score* score;
    const uint32_t trackNumber;
    const bool trackShown;

    void toggleShown(bool show);
};

#endif // EDITTRACKSHOWN_H