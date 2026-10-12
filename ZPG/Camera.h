#pragma once

class ShaderProgram;
class Camera
{
  private:
    ShaderProgram* m_shaderProgram;
    
  public:
    Camera(ShaderProgram* shaderProgram);
    void metoda();
};