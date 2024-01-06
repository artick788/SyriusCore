struct VSin{
    float3 lPosition: Position;
    float3 lColor: Color;
    float2 lTexCoord: TexCoord;
};

struct VSOut{
    float4 position: SV_Position;
    float4 color: Color;
    float2 texCoord: TexCoord;
};

cbuffer ProjectionData: register(b0){
    matrix<float, 4, 4> perspective;
    matrix<float, 4, 4> orthogonal;
};

cbuffer CameraData: register(b1){
    matrix<float, 4, 4> view;
};

cbuffer ModelData: register(b2){
    matrix<float, 4, 4> model;
}

VSOut main(VSin input){
    VSOut output;
    output.position = mul(model, float4(input.lPosition, 1.0f));
    output.position = mul(view, output.position);
    output.position = mul(perspective, output.position);
    output.color = float4(input.lColor, 1.0f);
    output.texCoord = input.lTexCoord;
    return output;
}