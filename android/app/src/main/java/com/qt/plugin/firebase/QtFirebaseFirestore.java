package com.qt.plugin.firebase;

import android.util.Log;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.firestore.*;
import com.qt.plugin.core.QtMobilePluginChannel;
import com.qt.plugin.core.QtMobilePluginDispatcher;
import com.qt.plugin.core.QtMobilePluginChannelException;
import com.qt.plugin.core.QtMobilePluginChannelMessage;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class QtFirebaseFirestore extends QtMobilePluginChannel {

    private final String CHANNEL_NAME = "com.qt.plugin.firebase.Firestore";
    private final String METHOD_INIT = "init";
    private final String METHOD_GET_DOCUMENTS = "getDocuments";
    private final String METHOD_UPDATE_DOCUMENT = "updateDocument";
    private final String METHOD_ADD_DOCUMENT = "addDocument";
    private final String METHOD_ADD_OR_UPDATE_DOCUMENT_MULTI = "addOrUpdateDocumentMulti";
    private final String METHOD_ADD_COLLECTION_LISTENER = "addCollectionListener";
    private final String METHOD_REMOVE_COLLECTION_LISTENER = "removeCollectionListener";

    private static String TAG = "QtFirebaseFirestore";
    private static FirebaseFirestore FIRE_STORE;
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

        String collectionName = message.firstArg();

        switch(message.getMethodName()){
            case METHOD_INIT:
                init();
            break;
            case METHOD_GET_DOCUMENTS:
                this.getDocuments(
                        collectionName,
                        message.getArg(1, 0), // limit
                        message.getArg(2, 0), // offset
                        message.getArg(3, null), // sort
                        message.getArg(4, null)); // order
            break;
            case METHOD_ADD_DOCUMENT:
                Map dataAdd = message.secondArg();
                this.addDocument(collectionName, dataAdd);
                break;
            case METHOD_UPDATE_DOCUMENT:
                Map dataUpdate = message.secondArg();
                this.updateDocument(collectionName, dataUpdate);
                break;
            case METHOD_ADD_OR_UPDATE_DOCUMENT_MULTI:
                List dataAddOrUpdate = message.secondArg();
                this.addOrUpdateMulti(collectionName, dataAddOrUpdate);
                break;
            case METHOD_ADD_COLLECTION_LISTENER:
                this.addCollectionListener(collectionName, message);
                break;
            case METHOD_REMOVE_COLLECTION_LISTENER:
                if(this.listeners.containsKey(message.getId())){
                    this.listeners.get(message.getId()).remove();
                }
                break;
            default:
                throw new QtMobilePluginChannelException(String.format("method %s not available", message.getMethodName()));
        }
    }

    public void init() {
        if(this.FIRE_STORE == null){
            try{
                Log.i(TAG, "Firebase init..");
                FIRE_STORE = FirebaseFirestore.getInstance();
                Log.i(TAG, "Firebase OK!");
                this.initOk = true;
            }catch(Exception e){                
                Log.w(TAG, "Firebase init error:", e);
                throw new QtMobilePluginChannelException(String.format("Firebase init error: $s", e.getMessage()), e);
            }
        }

    }

    public void getDocuments(final String collection, int limit, int offset, String sort, String order){

        Log.i(TAG, "getCollection " + collection);

        if(!this.initOk){
            Log.i(TAG, "firestore not init!");
            throw new QtMobilePluginChannelException("Firebase not initialized");
        }

        Query query = FIRE_STORE.collection(collection);

        if(limit > 0){
            query.limit(limit);
        }
        query.startAt(offset);

        if(sort != null) {
            query.orderBy(sort, order != "desc" ? Query.Direction.ASCENDING : Query.Direction.DESCENDING);
        }

        query.get().addOnCompleteListener(new OnCompleteListener<QuerySnapshot>() {
            @Override
            public void onComplete(@NonNull Task<QuerySnapshot> task) {
                Log.i(TAG, "onComplete");
                if (task.isSuccessful()) {
                    Log.i(TAG, "isSuccessful");

                    List<Map<String,Object>> results = new LinkedList<Map<String, Object>>();

                    for (QueryDocumentSnapshot document : task.getResult()) {
                        results.add(document.getData());
                    }

                    Log.i(TAG, "call c++ from java");
                    sendResult(collection, results);

                } else {
                    Log.w(TAG, "Error getting documents.", task.getException());
                    sendError(task.getException(), "firebase task error: " + task.getException().getMessage());
                }
            }
        });
        Log.i(TAG, "firestireRead java called from c++.. done");
    }

    public void addOrUpdate(String collection, Map data){
        Object id = data.get("id");
        if(id == null){
            addDocument(collection, data);
        }else{
            updateDocument(collection, data);
        }
    }

    public void addDocument(final String collection, Map data){
        Log.i(TAG, "addDocument " + collection);

        if(!this.initOk){
            Log.i(TAG, "firestore not init!");
            throw new QtMobilePluginChannelException("Firebase not initialized");
        }

        DocumentReference doc = FIRE_STORE.collection(collection)
                .document();

        doc.set(data)
                .addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if(task.isSuccessful()){
                            sendResult(collection, doc.getId());
                        }else {
                            Log.w(TAG, "Error add document.", task.getException());
                            sendError(task.getException(), "firebase task error: " + task.getException().getMessage());
                        }
                    }
                });
    }

    public void updateDocument(final String collection, Map data){
        Log.i(TAG, "updateDocument " + collection);

        if(!this.initOk){
            Log.i(TAG, "firestore not init!");
            throw new QtMobilePluginChannelException("Firebase not initialized");
        }

        Object id = data.get("id");

        if(id == null){
            sendError(null, "Document id not set");
            return;
        }

        DocumentReference doc = FIRE_STORE.collection(collection)
                .document(id.toString());

        doc.set(data)
                .addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if(task.isSuccessful()){
                            sendResult(collection, doc.getId());
                        }else {
                            Log.w(TAG, "Error update document.", task.getException());
                            sendError(task.getException(), "firebase task error: " + task.getException().getMessage());
                        }
                    }
                });
    }

    public void addOrUpdateMulti(final String collection, List data){
        Log.i(TAG, "addCollection " + collection);

        if(!this.initOk){
            Log.i(TAG, "firestore not init!");
            throw new QtMobilePluginChannelException("Firebase not initialized");
        }

        CollectionReference col = FIRE_STORE.collection(collection);

        FIRE_STORE.runTransaction(new Transaction.Function<Object>() {
            @Nullable
            @Override
            public Object apply(@NonNull Transaction transaction) throws FirebaseFirestoreException {

                for(Object it : data){
                    Map item = (Map)it;
                    Object id = item.get("id");
                    DocumentReference docRef = null;

                    if(id != null){
                        docRef = col.document(id.toString());
                        transaction.update(docRef, item);
                    } else {
                        docRef = col.document();
                        transaction.set(docRef, it);
                    }

                    item.put("id", docRef.getId());
                }

                return null;
            }
        }).addOnCompleteListener(new OnCompleteListener<Object>() {
            @Override
            public void onComplete(@NonNull Task<Object> task) {
                if(task.isSuccessful()){
                    sendResult(data);
                }else{
                    Log.w(TAG, "Error addOrUpdate document.", task.getException());
                    sendError(task.getException(), "firebase task error: " + task.getException().getMessage());
                }
            }
        });
    }

    public void addCollectionListener(String collection, final QtMobilePluginChannelMessage message){
        Log.i(TAG, "addCollectionListener");

        if(listeners.containsKey(message.getId())){
            Log.i(TAG, "listener " + message.getId() + " already exists");
            return;
        }

        ListenerRegistration registration = FIRE_STORE.collection(collection).addSnapshotListener(new EventListener<QuerySnapshot>() {
            @Override
            public void onEvent(@Nullable QuerySnapshot value, @Nullable FirebaseFirestoreException error) {
                if(error != null){
                    Log.w(TAG, "Error listen.", error.fillInStackTrace());
                    sendError(error.fillInStackTrace(), "firebase listen error: " + error.getMessage());
                }else{

                    List<Map> data = new LinkedList<>();

                    for(DocumentSnapshot doc : value.getDocuments()){
                        data.add(doc.getData());
                    }

                    sendResult(data, message);
                }
            }
        });

        listeners.put(message.getId(), registration);
    }
}
