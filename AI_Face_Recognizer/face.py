import cv2
import face_recognition
import os

# 1. Load and encode your reference face
ref_image_path = "fang.jpg"
if not os.path.exists(ref_image_path):
    print(f"Error: Reference image '{ref_image_path}' not found!")
    exit(1)

ref_img = face_recognition.load_image_file(ref_image_path)
ref_encodings = face_recognition.face_encodings(ref_img)
if not ref_encodings:
    print(f"Error: No faces found in reference image '{ref_image_path}'.")
    exit(1)
ref_encoding = ref_encodings[0]

# 2. Open webcam feed
video_capture = cv2.VideoCapture(0)

while True:
    ret, frame = video_capture.read()
    if not ret:
        break

    # Resize frame for faster processing
    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
    rgb_small_frame = cv2.cvtColor(small_frame, cv2.COLOR_BGR2RGB)

    # Detect faces and encodings
    face_locations = face_recognition.face_locations(rgb_small_frame)
    face_encodings = face_recognition.face_encodings(rgb_small_frame, face_locations)

    # Process each face found in the frame
    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        # See if the face is a match for the known face(s)
        matches = face_recognition.compare_faces([ref_encoding], face_encoding, tolerance=0.5)

        if True in matches:
            # Scale back up face location since the frame we detected in was scaled to 1/4 size
            top *= 4
            right *= 4
            bottom *= 4
            left *= 4

            # Draw a box around the face
            cv2.rectangle(frame, (left, top), (right, bottom), (0, 255, 0), 2)

            # Draw a label with a name below the face
            cv2.putText(frame, "Fang (You)", (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

    cv2.imshow("Webcam - Your Face Only", frame)
    if cv2.waitKey(1) == ord("q"):
        break

video_capture.release()
cv2.destroyAllWindows()
