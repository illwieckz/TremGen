#! /usr/bin/env bash

# Author: Thomas Debesse
# License: CC0 1.0
# https://creativecommons.org/publicdomain/zero/1.0/

repo_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
cd "${repo_dir}"

set -u -e -o pipefail

_error () {
	printf 'ERROR: %s\n' "${1}" >&2
	exit 1
}

writeArenaFile () {
	sed -e 's/\\t/\t/g' > "${3}" <<-EOF
	{
	\tmap "${2}"
	\tlongname "TremGen#${1}"
	\ttype "tremulous"
	}
	EOF
}

writeGameFile () {
	cat > "${1}" <<-EOF
	unvanquished
	EOF
}

writeDepsFile () {
	cat > "${1}" <<-EOF
	res-tremgen
	EOF
}

_generate () {
	mkdir -p "${maps_dir}"
	./tremgen "${seed}" "${map_file}"
	writeDepsFile "${deps_file}"

	mkdir -p "${meta_dir}"
	./minimap "${seed}" "${levelshot_file}"
	writeArenaFile "${seed}" "${map_name}" "${arena_file}"

	mkdir -p "${urcheon_dir}"
	writeGameFile "${game_file}"
}

_edit () {
	netradiant "$(realpath "${map_file}")"
}

_build () {
	if [ ! -d "${source_dpkdir}" ]
	then
		_error "not a directory: ${source_dpkdir}"
	fi

	urcheon build -cm -mp fast "${resource_dpkdir}" "${source_dpkdir}"
}

_load () {
	unvanquished -pakpath "$(realpath data/build/test)" +devmap "${map_name}"
}

if [ -n "${1:-}" ]
then
	command="${1}"
	shift
else
	_error 'missing command'
fi

if [ -n "${1:-}" ]
then
	if [ "${1}" = 'new' ]
	then
		if [ "${command}" = 'generate' ]
		then
			seed="$(date +%N)"
		else
			_error '“new” pseudo-seed is only supported by “generate” commandd'
		fi
	else
		seed="${1}"
	fi
else
	if [ -f 'seed.txt' ]
	then
		seed="$(cat 'seed.txt')"
	else
		seed="$(date +%N)"
	fi
fi

printf "${seed}" > 'seed.txt'

map_name="tremgen-${seed}"

tremgen_pakpath='data/src'

resource_dpkdir="${tremgen_pakpath}/res-tremgen_src.dpkdir"

source_dpkdir="${tremgen_pakpath}/map-${map_name}_src.dpkdir"
deps_file="${source_dpkdir}/DEPS"

urcheon_dir="${source_dpkdir}/.urcheon"
game_file="${urcheon_dir}/game.txt"

maps_dir="${source_dpkdir}/maps"
map_file="${maps_dir}/${map_name}.map"

meta_dir="${source_dpkdir}/meta/${map_name}"
levelshot_file="${meta_dir}/${map_name}.tga"
arena_file="${meta_dir}/${map_name}.arena"

case "${command:-}" in
	'generate'|'edit'|'build'|'load')
		"_${command}" "${seed}"
	;;
	*)
		_error "unknown command “${command}”"
	;;
esac
