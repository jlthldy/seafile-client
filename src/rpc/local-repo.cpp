#include <glib-object.h>

#include "utils/utils.h"
#include "local-repo.h"

LocalRepo LocalRepo::fromGObject(GObject *obj)
{
    char *id = NULL;
    char *name = NULL;
    char *desc = NULL;
    char *worktree = NULL;

    gboolean encrypted;
    gboolean auto_sync;
    gint64 last_sync_time;

    g_object_get (obj,
                  "id", &id,
                  "name", &name,
                  "desc", &desc,
                  "encrypted", &encrypted,
                  "worktree", &worktree,
                  "auto-sync", &auto_sync,
                  "last-sync-time", &last_sync_time,
                  NULL);

    LocalRepo repo;
    repo.id = QString::fromUtf8(id);
    repo.name = QString::fromUtf8(name);
    repo.description = QString::fromUtf8(desc);
    repo.worktree = QString::fromUtf8(worktree);
    repo.encrypted = encrypted;
    repo.auto_sync = auto_sync;
    repo.last_sync_time = last_sync_time;

    g_free (id);
    g_free (name);
    g_free (desc);
    g_free (worktree);

    return repo;
}

void LocalRepo::setSyncInfo(QString state, QString error)
{
    // qDebug("error: %s\n", toCStr(error));
    // qDebug("state: %s\n", toCStr(state));
    if (error.length() > 0) {
        translateSyncError(error);
    } else {
        translateSyncState(state);
    }
}

void LocalRepo::translateSyncState(QString status)
{
    if (status == "synchronized") {
        sync_state_str = QObject::tr("synchronized");
        sync_state = SYNC_STATE_DONE;

    } else if (status == "committing") {
        sync_state_str = QObject::tr("indexing files");
        sync_state = SYNC_STATE_ING;

    } else if (status == "initializing") {
        sync_state_str = QObject::tr("sync initializing");
        sync_state = SYNC_STATE_ING;

    } else if (status == "downloading") {
        sync_state_str = QObject::tr("downloading");
        sync_state = SYNC_STATE_ING;

    } else if (status == "uploading") {
        sync_state_str = QObject::tr("uploading");
        sync_state = SYNC_STATE_ING;

    } else if (status == "merging") {
        sync_state_str = QObject::tr("sync merging");
        sync_state = SYNC_STATE_ING;

    } else if (status == "waiting for sync") {
        sync_state_str = QObject::tr("waiting for sync");
        sync_state = SYNC_STATE_WAITING;

    } else if (status == "relay not connected") {
        sync_state_str = QObject::tr("server not connected");
        sync_state = SYNC_STATE_WAITING;

    } else if (status == "relay authenticating") {
        sync_state_str = QObject::tr("server authenticating");
        sync_state = SYNC_STATE_WAITING;

    } else if (status == "auto sync is turned off") {
        sync_state_str = QObject::tr("auto sync is turned off");
        sync_state = SYNC_STATE_DISABLED;

    } else {
        qDebug("unknown sync status: %s\n", toCStr(status));
        sync_state_str = QObject::tr("unknown");
        sync_state = SYNC_STATE_UNKNOWN;
    }
}

void LocalRepo::translateSyncError(QString error)
{
    sync_state = SYNC_STATE_ERROR;

    if (error == "relay not connected") {
        sync_error_str = QObject::tr("server not connected");

    } else if (error == "Server has been removed") {
        sync_error_str = QObject::tr("Server has been removed");

    } else if (error == "You have not login to the server") {
        sync_error_str = QObject::tr("You have not login to the server");

    } else if (error == "You do not have permission to access this repo") {
        sync_error_str = QObject::tr("You do not have permission to access this library");

    } else if (error == "The storage space of the repo owner has been used up") {
        sync_error_str = QObject::tr("The storage space of the library owner has been used up");

    } else if (error == "Remote service is not available") {
        sync_error_str = QObject::tr("Remote service is not available");

    } else if (error == "Access denied to service. Please check your registration on relay.") {
        sync_error_str = QObject::tr("Access denied to service.");

    } else if (error == "Internal data corrupted.") {
        sync_error_str = QObject::tr("Internal data corrupted.");

    } else if (error == "Failed to start upload.") {
        sync_error_str = QObject::tr("Failed to start upload.");

    } else if (error == "Error occured in upload.") {
        sync_error_str = QObject::tr("Error occured in upload.");

    } else if (error == "Failed to start download.") {
        sync_error_str = QObject::tr("Failed to start download.");

    } else if (error == "Error occured in download.") {
        sync_error_str = QObject::tr("Error occured in download.");

    } else if (error == "No such repo on relay.") {
        sync_error_str = QObject::tr("Library is deleted on server");

    } else if (error == "Unknown error.") {
        sync_error_str = QObject::tr("Unknown error.");
    } else {
        sync_error_str = error;
    }
};

QIcon LocalRepo::getIcon() const
{
    if (encrypted) {
        return QIcon(":/images/encrypted-repo.png");
    } else {
        return QIcon(":/images/repo.png");
    }
}
