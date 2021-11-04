package com.qt.plugin.firebase;

import android.net.Uri;
import android.util.Log;

import androidx.annotation.NonNull;

import com.google.android.gms.tasks.Continuation;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.firestore.ListenerRegistration;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.OnProgressListener;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.UploadTask;
import com.qt.plugin.core.QtMobilePluginChannel;
import com.qt.plugin.core.QtMobilePluginDispatcher;
import com.qt.plugin.core.QtMobilePluginChannelException;
import com.qt.plugin.core.QtMobilePluginChannelMessage;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

public class QFirebaseStorage extends QtMobilePluginChannel {

    private final String CHANNEL_NAME = "com.qt.plugin.firebase.Storage";
    private final String METHOD_INIT = "init";

    private static String TAG = "QtFirebaseStorage";
    private static FirebaseStorage STORAGE;
    private QtMobilePluginChannelMessage currentMessage;
    private boolean initOk;
    private Map<String, ListenerRegistration> listeners = new HashMap<>();

    @Override
    public String getChannelName() {
        return CHANNEL_NAME;
    }

    @Override
    public QtMobilePluginChannelMessage getCurrentMessage() {
        return currentMessage;
    }

    @Override
    public void register(){
        QtMobilePluginDispatcher.channelRegister(CHANNEL_NAME, this);
    }

    @Override
    public void callMethod(QtMobilePluginChannelMessage message){

        Log.i(TAG, "callMethod " + message.getMethodName());

        this.currentMessage = message;

        String bucketName = message.firstArg();

        switch(message.getMethodName()){
            case METHOD_INIT:
                init(bucketName);
                break;

            default:
                throw new QtMobilePluginChannelException(String.format("method %s not available", message.getMethodName()));
        }
    }

    public void init(String bucketName) {
        if(this.STORAGE == null){
            try{
                Log.i(TAG, "Storage init bucket " + bucketName);
                STORAGE = FirebaseStorage.getInstance(String.format("gs://%s", bucketName));;
                Log.i(TAG, "Storage OK!");
                this.initOk = true;
            }catch(Exception e){
                Log.w(TAG, "Storage init error:", e);
                throw new QtMobilePluginChannelException(String.format("Storage init error: $s", e.getMessage()), e);
            }
        }
    }
    public void upload(String filePath, String key){
        if(STORAGE == null){
            throw new QtMobilePluginChannelException("storage not initialized");
        }

        StorageReference storageRef = STORAGE.getReference().child(key);

        Uri file = Uri.fromFile(new File(filePath));
        UploadTask uploadTask = storageRef.putFile(file);

        // Register observers to listen for when the download is done or if it fails
        uploadTask.addOnFailureListener(new OnFailureListener() {
            @Override
            public void onFailure(@NonNull Exception exception) {
                // Handle unsuccessful uploads
            }
        }).addOnSuccessListener(new OnSuccessListener<UploadTask.TaskSnapshot>() {
            @Override
            public void onSuccess(UploadTask.TaskSnapshot taskSnapshot) {
                // taskSnapshot.getMetadata() contains file metadata such as size, content-type, etc.
                // ...

            }
        }).addOnProgressListener(new OnProgressListener<UploadTask.TaskSnapshot>() {
            @Override
            public void onProgress(@NonNull UploadTask.TaskSnapshot snapshot) {

            }
        });
    }

    //https://firebase.google.com/docs/storage/android/download-files
    public void getDownloadUrl(StorageReference storageRef, UploadTask uploadTask){

        Task<Uri> urlTask = uploadTask.continueWithTask(new Continuation<UploadTask.TaskSnapshot, Task<Uri>>() {
            @Override
            public Task<Uri> then(@NonNull Task<UploadTask.TaskSnapshot> task) throws Exception {
                if (!task.isSuccessful()) {
                    throw task.getException();
                }

                // Continue with the task to get the download URL
                return storageRef.getDownloadUrl();
            }
        }).addOnCompleteListener(new OnCompleteListener<Uri>() {
            @Override
            public void onComplete(@NonNull Task<Uri> task) {
                if (task.isSuccessful()) {
                    Uri downloadUri = task.getResult();
                } else {
                    // Handle failures
                    // ...
                }
            }
        });
    }

}
