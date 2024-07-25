#/bin/bash
prompt_user() {
    read -p "Confirm full : " -n 1 -r
    echo

    response="${REPLY:-n}"
    case "$response" in
        [Yy]* ) echo "Continuing...";;
        [Nn]* | '' ) echo "Cancelled."; exit 1;;
        * ) echo "Invalid input."; exit 1;;
    esac
}

prompt_user

./clear.sh && ./fetch.sh && ./generate.sh && ./build.sh