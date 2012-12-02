# MJS version number.
set(MJS_VERSION_MAJOR "1")
set(MJS_VERSION_MINOR "0")
set(MJS_VERSION_PATCH "0")

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_TAG)

