function(grab_git_info hash date message)
    find_package(Git REQUIRED)
    # the commit's SHA1, and whether the building workspace was dirty or not
    execute_process(COMMAND
      "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      OUTPUT_VARIABLE GIT_SHA1
      ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    
    # the date of the commit
    execute_process(COMMAND
      "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      OUTPUT_VARIABLE GIT_DATE
      ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    
    # the subject of the commit
    execute_process(COMMAND
      "${GIT_EXECUTABLE}" log -1 --format=%s
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
      ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

    message("GIT_SHA1: ${GIT_SHA1}")
    message("GIT_DATE: ${GIT_DATE}")
    message("GIT_COMMIT_SUBJECT: ${GIT_COMMIT_SUBJECT}")

    set(${hash} "${GIT_SHA1}" PARENT_SCOPE)
    set(${date} "${GIT_DATE}" PARENT_SCOPE)
    set(${message} "${GIT_COMMIT_SUBJECT}" PARENT_SCOPE)
endfunction()
