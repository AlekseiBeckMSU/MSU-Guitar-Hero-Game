/**
 * @file GameApp.h
 * @author Alex Beck
 *
 *
 */

#ifndef SPARTANHERO__GAMEAPP_H
#define SPARTANHERO__GAMEAPP_H

#include <wx/wx.h>

/**
 * GameApp represents the application
 */
class GameApp : public wxApp
{
private:

public:

    bool OnInit() override;
};

#endif //SPARTANHERO__GAMEAPP_H
