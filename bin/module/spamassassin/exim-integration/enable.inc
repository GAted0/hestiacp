#!/bin/bash

hestia_module_spamassassin_exim-integration_enable() {
    source $HESTIA/bin/module/func.inc

    if ! hestia_module_isinstalled 'mta' && [ ! "$param_force" ]; then
        echo "MTA module is not installed. See 'hestia module info mta'."
        return 1
    fi

    module_variant=$(hestia_module_getvariant mta)
    if [ "$module_variant" != 'exim' ] && [ ! "$param_force" ]; then
        echo "The installed MTA module is not Exim. See 'hestia module info mta'."
        return 1
    fi

    echo "Enabling SpamAssassin-Exim integration..."
    /usr/bin/sed -i "/^#SPAMASSASSIN\s*=\s*/ s/#*//" "$OSAL_PATH_EXIM_CONF"
    /usr/bin/sed -i "/^#SPAM_SCORE\s*=\s*/ s/#*//" "$OSAL_PATH_EXIM_CONF"

    osal_service_restart $OSAL_SERVICE_EXIM
    check_result $? "Exim restart failed"
}