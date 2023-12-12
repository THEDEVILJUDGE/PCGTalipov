from flask import Flask, render_template
from flask_wtf import FlaskForm
from wtforms import FloatField, SubmitField
import numpy as np
import plotly.subplots as sp
import plotly.graph_objects as go
from scipy.spatial.transform import Rotation

app = Flask(__name__)
app.config['SECRET_KEY'] = 'mysecretkey'

class TransformationForm(FlaskForm):
    scale = FloatField('Scale', default=1.5)
    translation = FloatField('Translation', default=1.0)
    rotation = FloatField('Rotation', default=45.0)
    submit = SubmitField('Update')

def interpolate_points(x, y, z, num_points=10):
    interpolated_x = np.interp(np.linspace(0, 1, num_points), [0, 1], [x[0], x[1]])
    interpolated_y = np.interp(np.linspace(0, 1, num_points), [0, 1], [y[0], y[1]])
    interpolated_z = np.interp(np.linspace(0, 1, num_points), [0, 1], [z[0], z[1]])
    return interpolated_x, interpolated_y, interpolated_z

@app.route('/', methods=['GET', 'POST'])
def index():
    form = TransformationForm()

    if form.validate_on_submit():
        scale_factor = form.scale.data
        translation_value = form.translation.data
        rotation_angle = form.rotation.data

        original_x_1 = np.array([5, 7, 5, 7, 5, 7, 5, 7, 5, 7, 5, 7, 5, 7, 5, 7, 3, 3, 9, 9, 3, 9, 4, 8, 5, 7, 9, 3, 9, 4, 8, 5, 7, 9, 3, 9, 4, 8, 5, 7, 5, 5, 7, 7])
        original_y_1 = np.array([0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 5, 7, 5, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 0, 7, 0])
        original_z_1 = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])

        original_x_2 = original_x_1 + 1
        original_y_2 = original_y_1
        original_z_2 = original_z_1

        original_x = np.concatenate([original_x_1, original_x_2])
        original_y = np.concatenate([original_y_1, original_y_2])
        original_z = np.concatenate([original_z_1, original_z_2])

        back_offset = 2
        back_z = original_z + back_offset

        new_original_x = []
        new_original_y = []
        new_original_z = []

        for i in range(len(original_x) - 1):
            x_interpolated, y_interpolated, z_interpolated = interpolate_points(
                [original_x[i], original_x[i + 1]],
                [original_y[i], original_y[i + 1]],
                [original_z[i], original_z[i + 1]]
            )
            new_original_x.extend(x_interpolated)
            new_original_y.extend(y_interpolated)
            new_original_z.extend(z_interpolated)

        original_x = np.array(new_original_x)
        original_y = np.array(new_original_y)
        original_z = np.array(new_original_z)

        scaled_x = scale_factor * original_x
        scaled_y = scale_factor * original_y
        scaled_z = scale_factor * original_z

        translated_x = scaled_x + translation_value
        translated_y = scaled_y + translation_value
        translated_z = scaled_z + translation_value

        rotation_axis = [1, 1, 1]
        rotation_matrix = Rotation.from_rotvec(np.radians(rotation_angle) * np.array(rotation_axis)).as_matrix()

        rotated_x, rotated_y, rotated_z = np.dot(rotation_matrix, np.array([translated_x, translated_y, translated_z]))

        # Create the 3D plot
        fig = go.Figure()
        fig.add_trace(go.Scatter3d(x=[0, 0], y=[-1, 1], z=[0, 0], mode='lines', line=dict(width=3, color='red')))
        fig.add_trace(go.Scatter3d(x=[-1, 1], y=[0, 0], z=[0, 0], mode='lines', line=dict(width=3, color='red')))
        fig.add_trace(go.Scatter3d(x=rotated_x, y=rotated_y, z=rotated_z, mode='markers+lines',
                                   marker=dict(size=8, color='blue'), line=dict(width=3, color='blue')))

        # Create the XY Projection plot
        fig_xy = go.Figure()
        fig_xy.add_trace(go.Scatter(x=rotated_x, y=rotated_y, mode='markers+lines', marker=dict(size=8, color='blue'), line=dict(width=3, color='blue')))

        # Create the XZ Projection plot
        fig_xz = go.Figure()
        fig_xz.add_trace(go.Scatter(x=rotated_x, y=rotated_z + back_offset, mode='markers+lines', marker=dict(size=8, color='blue'), line=dict(width=3, color='blue')))

        # Create the YZ Projection plot
        fig_yz = go.Figure()
        fig_yz.add_trace(go.Scatter(x=rotated_y, y=rotated_z + back_offset, mode='markers+lines', marker=dict(size=8, color='blue'), line=dict(width=3, color='blue')))

        three_d_model = fig.to_html(full_html=False)
        xy_projection = fig_xy.to_html(full_html=False)
        xz_projection = fig_xz.to_html(full_html=False)
        yz_projection = fig_yz.to_html(full_html=False)

        return render_template('index.html', form=form, three_d_model=three_d_model, xy_projection=xy_projection, xz_projection=xz_projection, yz_projection=yz_projection)

    return render_template('index.html', form=form, three_d_model=None, xy_projection=None, xz_projection=None, yz_projection=None)

if __name__ == '__main__':
    app.run(debug=True)
