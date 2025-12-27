
vector<string> getMapFiles(const string& directoryPath, const string& extension = ".map") {
    vector<string> maps;

    string searchPath = directoryPath + "\\*" + extension;

    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Проверяем, не директория ли это
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                string filename = findData.cFileName;
                maps.push_back(filename);
            }
        } while (FindNextFileA(hFind, &findData) != 0);

        FindClose(hFind);
    }

    // Сортируем по алфавиту
    sort(maps.begin(), maps.end());

    return maps;
}


string selectMapMenu(RenderWindow& window, Settings& mysettings) {

    MyText menu_text("myfonts/arial_bolditalicmt.ttf", "Select map", 72);
    menu_text.setVisible(true);
    menu_text.setColor(Color::White);
    menu_text.setPosition((mysettings.width - 400) / 2, mysettings.height * 0.1);

    MyText maps_list("myfonts/arialmt.ttf", "");
    maps_list.setVisible(true);
    maps_list.setColor(Color::White);
    maps_list.setPosition((mysettings.width - 200) / 2, mysettings.height * 0.3);

    MyText selected_map("myfonts/arialmt.ttf", "", 28);
    selected_map.setVisible(true);
    selected_map.setColor(Color::White);
    selected_map.setPosition((mysettings.width - 200) / 2, mysettings.height * 0.7);

    string list = "";
    vector <string> maps = getMapFiles("maps", ".txt");
    for (auto i : maps) {
        list += i += "\n";
    }
    cout << list;
    maps_list.setString(list);


    bool runWhile = 1;

    string out = "fastrunner.txt";//default
    int index = 0;
    Event event;
    while (runWhile) {


        while (window.pollEvent(event)) { if (event.type == Event::Closed) window.close(); }

        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            index--;
            while (Keyboard::isKeyPressed(Keyboard::Up));
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            index++;
            while (Keyboard::isKeyPressed(Keyboard::Down));
        }

        if (index < 0) index = 0;
        if (index > maps.size() - 1)index = maps.size() - 1;
        out = maps[index];

        if (Keyboard::isKeyPressed(Keyboard::Enter))
            runWhile = 0;

        selected_map.setString(out);
        window.clear();
        maps_list.draw(window);
        menu_text.draw(window);
        selected_map.draw(window);
        window.display();
    }
    return out;
}