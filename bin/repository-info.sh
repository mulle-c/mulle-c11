#! /bin/sh

HOMEPAGE='https://github.com/mulle-nat/${NAME}'
ORIGIN=public                                    # git repo to push
REMOTEROOTDIR="mulle-kybernetik"

REMOTEHOST="https://github.com"
REMOTEURL="${REMOTEHOST}/${REMOTEROOTDIR}"
ARCHIVEURL='${REMOTEURL}/${NAME}/archive/${VERSION}.tar.gz'  # ARCHIVEURL will be evaled later! keep it in single quotes

: