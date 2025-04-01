@startuml
start
:Works on a form of CurrentPositionComponent;
:Input direction (required);
:Input world (optional);
:Input isSprinting (optional);

if (is Sprinting?) then (yes)
    :Multiply direction by 2;
endif

:Calculate new location;

if (world exists?) then (no)
    :Set new location;
    :Return;
    stop
endif

:Test if blocked;

if (blocked?) then (yes)
    :Test if space above blocked;
    if (blocked above?) then (yes)
        :Don't move;
        :Return;
        stop
    else (no)
        :Test space above above;
        if (blocked above above?) then (yes)
            :Don't move;
            :Return;
            stop
        else (no)
            :Test blocked above current;
            if (blocked above current?) then (yes)
                :Don't move;
                :Return;
                stop
            else (no)
                :new location.y += 2;
                :Set new location;
                :Return;
                stop
            endif
        endif
    endif
else (no)
    :Test if space above blocked;
    if (blocked above?) then (yes)
        :Don't move;
        :Return;
        stop
    else (no)
        :Test if space below blocked;
        if (blocked below?) then (yes)
            :Set new location;
            :Return;
            stop
        else (no)
            :new location.y -= 2;
            :Set new location;
            :Return;
            stop
        endif
    endif
endif

@enduml
