attribute vec4 vertexPosition;

uniform mat4 projection;
uniform mat4 viewModel;

void main()
{    
    gl_Position = projection * viewModel * vertexPosition;

}