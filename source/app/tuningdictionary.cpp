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

#include "tuningdictionary.h"

#include <QDebug>
#include <QMutexLocker>
#include <QtConcurrentRun>
#include <QCoreApplication>
#include <fstream>

#include <powertabdocument/powertabinputstream.h>
#include <powertabdocument/powertaboutputstream.h>
#include <powertabdocument/powertabfileheader.h>
#include <powertabdocument/tuning.h>

TuningDictionary::TuningDictionary()
{
}

/// Load the tuning dictionary from a file.
void TuningDictionary::load()
{
    try
    {
        std::ifstream tuningStream(tuningFilePath().c_str());
        PowerTabInputStream inputStream(tuningStream);

        std::vector<boost::shared_ptr<Tuning> > newTunings;
        inputStream.ReadVector(newTunings, PowerTabFileHeader::Version_2_0);

        QMutexLocker lock(&mutex);
        Q_UNUSED(lock);
        tunings = newTunings;
    }
    catch (std::exception &e)
    {
        qDebug() << "Error loading tuning dictionary.";
        qDebug() << "Exception: " << e.what();
    }
}

/// Saves the tuning dictionary to a file.
void TuningDictionary::save()
{
    try
    {
        std::ofstream tuningStream(tuningFilePath().c_str());
        PowerTabOutputStream outputStream(tuningStream);

        QMutexLocker lock(&mutex);
        Q_UNUSED(lock);
        outputStream.WriteVector(tunings);
    }
    catch (std::exception &e)
    {
        qDebug() << "Error loading tuning dictionary.";
        qDebug() << "Exception: " << e.what();
    }
}

/// Loads the tuning dictionary, and runs in a separate thread.
void TuningDictionary::loadInBackground()
{
    QtConcurrent::run(this, &TuningDictionary::load);
}

std::string TuningDictionary::tuningFilePath()
{
    QString path = QCoreApplication::applicationDirPath() +
            "/data/tunings.dat";
    return path.toStdString();
}
